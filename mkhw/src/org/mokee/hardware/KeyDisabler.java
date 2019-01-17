/*
 * Copyright (C) 2014 The CyanogenMod Project
 * Copyright (C) 2018 The MoKee Open Source Project
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

package org.mokee.hardware;

import org.mokee.internal.util.FileUtils;

/*
 * Disable capacitive keys
 *
 * This is intended for use on devices in which the capacitive keys
 * can be fully disabled for replacement with a soft navbar. You
 * really should not be using this on a device with mechanical or
 * otherwise visible-when-inactive keys
 */

public class KeyDisabler {

    private static final String FILE_GOODIX =
            "/sys/devices/soc/soc:goodix_fp/key_disabled";

    private static final String FILE_FPC =
            "/sys/devices/soc/soc:fpc1020/key_disabled";

    private static final String FILE_NAV_MIDDLE =
            "/proc/keypad/nav_middle";

    private static final String KEY_HOME = "172";
    private static final String KEY_POWER = "116";

    /*
     * All HAF classes should export this boolean.
     * Real implementations must, of course, return true
     */

    public static boolean isSupported() {
        return FileUtils.isFileWritable(FILE_NAV_MIDDLE) && (
                    FileUtils.isFileWritable(FILE_GOODIX) ||
                    FileUtils.isFileWritable(FILE_FPC));
    }

    /*
     * Are the keys currently blocked?
     */

    public static boolean isActive() {
        final boolean blockedHome = !KEY_HOME.equals(FileUtils.readOneLine(FILE_NAV_MIDDLE));
        final boolean blockedBack;

        final String valueGoodix = FileUtils.readOneLine(FILE_GOODIX);
        final String valueFpc = FileUtils.readOneLine(FILE_FPC);

        if (valueGoodix != null) {
            blockedBack = !valueGoodix.equals("0");
        } else if (valueFpc != null) {
            blockedBack = !valueFpc.equals("0");
        } else {
            blockedBack = false;
        }

        return blockedHome && blockedBack;
    }

    /*
     * Disable capacitive keys
     */

    public static boolean setActive(boolean state) {
        final String value = state ? "1" : "0";
        return FileUtils.writeLine(FILE_NAV_MIDDLE, state ? KEY_POWER : KEY_HOME) && (
                FileUtils.writeLine(FILE_GOODIX, value) ||
                FileUtils.writeLine(FILE_FPC, value));
    }

}
