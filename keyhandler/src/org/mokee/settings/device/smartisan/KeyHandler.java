/*
 * Copyright (C) 2018-2019 The MoKee Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.mokee.settings.device.smartisan;

import android.content.Context;
import android.hardware.input.InputManager;
import android.os.Handler;
import android.os.Looper;
import android.os.PowerManager;
import android.os.SystemClock;
import android.os.Vibrator;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.view.ViewConfiguration;
import android.view.WindowManager;

import com.android.internal.os.DeviceKeyHandler;
import com.android.internal.util.ScreenshotHelper;

import mokee.providers.MKSettings;

import org.mokee.internal.util.FileUtils;

public class KeyHandler implements DeviceKeyHandler {

    private static final String TAG = "KeyHandler";

    private static final int KEY_HOME_TOUCH_FPC = 0;
    private static final int KEY_HOME_TOUCH_GOODIX = 1;
    private static final int KEY_HOME_PRESS = 2;
    private static final int KEY_LEFT_UP = 3;
    private static final int KEY_LEFT_DOWN = 4;
    private static final int KEY_RIGHT_UP = 5;
    private static final int KEY_RIGHT_DOWN = 6;

    private final KeyInfo[] keys = new KeyInfo[] {
        new KeyInfo("home_touch", "uinput-fpc"),
        new KeyInfo("home_touch", "gf3208"),
        new KeyInfo("home_press", "qpnp_pon"),
        new KeyInfo("left_up", "gpio-keys"),
        new KeyInfo("left_down", "gpio-keys"),
        new KeyInfo("right_up", "qpnp_pon"),
        new KeyInfo("right_down", "gpio-keys"),
    };

    private final int longPressTimeout = ViewConfiguration.getLongPressTimeout();
    private final int longLongPressTimeout = 2000;
    private final int doubleTapTimeout = ViewConfiguration.getDoubleTapTimeout();

    private Context context;
    private Vibrator vibrator;
    private PowerManager pm;
    private ScreenshotHelper screenshotHelper;

    private long lastHomeTouchMillis = 0;

    private boolean ongoingPowerLongPress = false;

    private int leftIndexPressed = -1;
    private int rightIndexPressed = -1;

    private Handler handler = new Handler(Looper.getMainLooper());

    private final Runnable triggerPartialScreenshot = new Runnable() {
        @Override
        public void run() {
            if (leftIndexPressed != -1 && rightIndexPressed != -1) {
                injectKey(keys[leftIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
                injectKey(keys[rightIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
                leftIndexPressed = -1;
                rightIndexPressed = -1;
                takeScreenshot(true);
            }
        }
    };

    public KeyHandler(Context context) {
        this.context = context;
        this.pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        this.screenshotHelper = new ScreenshotHelper(context);
        vibrator = context.getSystemService(Vibrator.class);
        if (vibrator == null || !vibrator.hasVibrator()) {
            vibrator = null;
        }
    }

    public KeyEvent handleKeyEvent(KeyEvent event) {
        boolean handled = false;
        handled = handleHomeTouchKeyEvent(event) || handled;
        handled = handleHomePressKeyEvent(event) || handled;
        handled = handleLeftKeyEvent(event) || handled;
        handled = handleRightKeyEvent(event) || handled;
        return handled ? null : event;
    }

    private boolean handleHomePressKeyEvent(KeyEvent event) {
        final KeyInfo keyHomePress = keys[KEY_HOME_PRESS];

        if (!keyHomePress.match(event)) {
            return false;
        }

        switch (event.getAction()) {
            case KeyEvent.ACTION_DOWN:
                injectKey(keyHomePress.keyCode, KeyEvent.ACTION_DOWN, 0);
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        injectKey(keyHomePress.keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
                        injectKey(KeyEvent.KEYCODE_POWER);
                        doHapticFeedback();
                    }
                }, "power_tap", longPressTimeout);
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        injectKey(KeyEvent.KEYCODE_POWER, KeyEvent.ACTION_DOWN, 0);
                        doHapticFeedback();
                        ongoingPowerLongPress = true;
                    }
                }, "power_hold", longLongPressTimeout);
                break;
            case KeyEvent.ACTION_UP:
                if (ongoingPowerLongPress) {
                    injectKey(KeyEvent.KEYCODE_POWER, KeyEvent.ACTION_UP, 0);
                    ongoingPowerLongPress = false;
                } else {
                    injectKey(keyHomePress.keyCode, KeyEvent.ACTION_UP, 0);
                    handler.removeCallbacksAndMessages("power_tap");
                    handler.removeCallbacksAndMessages("power_hold");
                }
                break;
        }

        return true;
    }

    private boolean handleHomeTouchKeyEvent(KeyEvent event) {
        // The sensor reports fake DOWN and UP per taps
        if (event.getAction() != KeyEvent.ACTION_UP) {
            return false;
        }

        KeyInfo matchedKey;

        if (keys[KEY_HOME_TOUCH_FPC].match(event)) {
            matchedKey = keys[KEY_HOME_TOUCH_FPC];
        } else if (keys[KEY_HOME_TOUCH_GOODIX].match(event)) {
            matchedKey = keys[KEY_HOME_TOUCH_GOODIX];
        } else {
            return false;
        }

        final long now = SystemClock.uptimeMillis();
        if (now - lastHomeTouchMillis < doubleTapTimeout) {
            injectKey(KeyEvent.KEYCODE_APP_SWITCH);
        } else {
            injectKey(matchedKey.keyCode);
        }

        lastHomeTouchMillis = now;

        return true;
    }

    private boolean handleLeftKeyEvent(KeyEvent event) {
        KeyInfo matchedKey;
        int matchedKeyIndex;

        if (keys[KEY_LEFT_UP].match(event)) {
            matchedKey = keys[KEY_LEFT_UP];
            matchedKeyIndex = KEY_LEFT_UP;
        } else if (keys[KEY_LEFT_DOWN].match(event)) {
            matchedKey = keys[KEY_LEFT_DOWN];
            matchedKeyIndex = KEY_LEFT_DOWN;
        } else {
            return false;
        }

        if (leftIndexPressed != -1 && leftIndexPressed != matchedKeyIndex) {
            injectKey(keys[leftIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
            leftIndexPressed = -1;
        }

        switch (event.getAction()) {
            case KeyEvent.ACTION_DOWN:
                if (rightIndexPressed != -1) {
                    injectKey(keys[rightIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
                    handler.postDelayed(triggerPartialScreenshot, "partial_screenshot", longPressTimeout);
                } else {
                    injectKey(matchedKey.keyCode, KeyEvent.ACTION_DOWN, 0);
                }
                if (pm.isInteractive()) {
                    leftIndexPressed = matchedKeyIndex;
                }
                break;
            case KeyEvent.ACTION_UP:
                if (rightIndexPressed != -1) {
                    takeScreenshot(false);
                    rightIndexPressed = -1;
                } else {
                    injectKey(matchedKey.keyCode, KeyEvent.ACTION_UP, 0);
                }
                handler.removeCallbacksAndMessages("partial_screenshot");
                leftIndexPressed = -1;
                break;
        }

        return true;
    }

    private boolean handleRightKeyEvent(KeyEvent event) {
        KeyInfo matchedKey;
        int matchedKeyIndex;

        if (keys[KEY_RIGHT_UP].match(event)) {
            matchedKey = keys[KEY_RIGHT_UP];
            matchedKeyIndex = KEY_RIGHT_UP;
        } else if (keys[KEY_RIGHT_DOWN].match(event)) {
            matchedKey = keys[KEY_RIGHT_DOWN];
            matchedKeyIndex = KEY_RIGHT_DOWN;
        } else {
            return false;
        }

        if (rightIndexPressed != -1 && rightIndexPressed != matchedKeyIndex) {
            injectKey(keys[rightIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
            rightIndexPressed = -1;
        }

        switch (event.getAction()) {
            case KeyEvent.ACTION_DOWN:
                if (leftIndexPressed != -1) {
                    injectKey(keys[leftIndexPressed].keyCode, KeyEvent.ACTION_UP, KeyEvent.FLAG_CANCELED);
                    handler.postDelayed(triggerPartialScreenshot, "partial_screenshot", longPressTimeout);
                } else {
                    injectKey(matchedKey.keyCode, KeyEvent.ACTION_DOWN, 0);
                }
                if (pm.isInteractive()) {
                    rightIndexPressed = matchedKeyIndex;
                }
                break;
            case KeyEvent.ACTION_UP:
                if (leftIndexPressed != -1) {
                    takeScreenshot(false);
                    leftIndexPressed = -1;
                } else {
                    injectKey(matchedKey.keyCode, KeyEvent.ACTION_UP, 0);
                }
                handler.removeCallbacksAndMessages("partial_screenshot");
                rightIndexPressed = -1;
                break;
        }

        return true;
    }

    private String getDeviceName(KeyEvent event) {
        final int deviceId = event.getDeviceId();
        final InputDevice device = InputDevice.getDevice(deviceId);
        return device == null ? null : device.getName();
    }

    private void injectKey(int code) {
        injectKey(code, KeyEvent.ACTION_DOWN, 0);
        injectKey(code, KeyEvent.ACTION_UP, 0);
    }

    private void injectKey(int code, int action, int flags) {
        final long now = SystemClock.uptimeMillis();
        InputManager.getInstance().injectInputEvent(new KeyEvent(
                        now, now, action, code, 0, 0,
                        KeyCharacterMap.VIRTUAL_KEYBOARD,
                        0, flags,
                        InputDevice.SOURCE_KEYBOARD),
                InputManager.INJECT_INPUT_EVENT_MODE_ASYNC);
    }

    private void doHapticFeedback() {
        if (vibrator == null) {
            return;
        }

        final boolean enabled = MKSettings.System.getInt(context.getContentResolver(),
                MKSettings.System.TOUCHSCREEN_GESTURE_HAPTIC_FEEDBACK, 1) != 0;
        if (enabled) {
            vibrator.vibrate(50);
        }
    }

    private void takeScreenshot(final boolean partial) {
        final int type = partial
                ? WindowManager.TAKE_SCREENSHOT_SELECTED_REGION
                : WindowManager.TAKE_SCREENSHOT_FULLSCREEN;

        screenshotHelper.takeScreenshot(type, true, true, handler);
    }

    private class KeyInfo {

        final String deviceName;
        final int scanCode;
        int deviceId;
        int keyCode;

        KeyInfo(String file, String deviceName) {
            int scanCode;
            this.deviceName = deviceName;
            try {
                scanCode = Integer.parseInt(FileUtils.readOneLine(
                        "/proc/keypad/" + file));
            } catch (NumberFormatException ignored) {
                scanCode = 0;
            }
            this.scanCode = scanCode;
        }

        boolean match(KeyEvent event) {
            if (deviceId == 0) {
                final String deviceName = getDeviceName(event);
                if (this.deviceName.equals(deviceName)) {
                    deviceId = event.getDeviceId();
                } else {
                    return false;
                }
            } else {
                if (deviceId != event.getDeviceId()) {
                    return false;
                }
            }

            if (event.getScanCode() == scanCode) {
                keyCode = event.getKeyCode();
            } else {
                return false;
            }

            return true;
        }

    }

}
