#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VIDEO_MAX_PLANES 8
#define V4L2_CID_PRIVATE_BASE       0x08000000
#define MSM_CAMERA_PRIV_CMD_MAX  20

#include "camera/QCamera2/stack/common/cam_types.h"
#include "camera/QCamera2/stack/common/cam_intf.h"

int main() {
    cam_capability_t *cap = (cam_capability_t *) malloc(sizeof(cam_capability_t));

    FILE *in = fopen("capability", "rb");
    fread(cap, sizeof(cam_capability_t), 1, in);
    fclose(in);

    printf("[%lu] version: %d\n", sizeof(cap->version), cap->version);
    printf("[%lu] position: %d\n", sizeof(cap->position), cap->position);
    printf("[%lu] auto_hdr_supported: %d\n", sizeof(cap->auto_hdr_supported), cap->auto_hdr_supported);
    printf("[%lu] isWnrSupported: %d\n", sizeof(cap->isWnrSupported), cap->isWnrSupported);
    printf("[%lu] supported_iso_modes_cnt: %zu\n", sizeof(cap->supported_iso_modes_cnt), cap->supported_iso_modes_cnt);
    for (int i = 0; i < cap->supported_iso_modes_cnt; i++) {
        printf("supported_iso_modes: [%d] %d\n", i, cap->supported_iso_modes[i]);
    }
    printf("[%lu] supported_flash_modes_cnt: %zu\n", sizeof(cap->supported_flash_modes_cnt), cap->supported_flash_modes_cnt);
    for (int i = 0; i < cap->supported_flash_modes_cnt; i++) {
        printf("supported_flash_modes: [%d] %d\n", i, cap->supported_flash_modes[i]);
    }
    printf("[%lu] zoom_ratio_tbl_cnt: %zu\n", sizeof(cap->zoom_ratio_tbl_cnt), cap->zoom_ratio_tbl_cnt);
    for (int i = 0; i < cap->zoom_ratio_tbl_cnt; i++) {
        printf("zoom_ratio_tbl: [%d] %d\n", i, cap->zoom_ratio_tbl[i]);
    }

    // for (int i = 0; i < sizeof(cap->smartisan_reversed1); i++) {
    //     printf("%02x ", cap->smartisan_reversed1[i]);
    // }
    // printf("\n");

    printf("[%lu] supported_effects_cnt: %zu\n", sizeof(cap->supported_effects_cnt), cap->supported_effects_cnt);
    for (int i = 0; i < cap->supported_effects_cnt; i++) {
        printf("supported_effects: [%d] %d\n", i, cap->supported_effects[i]);
    }
    printf("[%lu] supported_scene_modes_cnt: %zu\n", sizeof(cap->supported_scene_modes_cnt), cap->supported_scene_modes_cnt);
    for (int i = 0; i < cap->supported_scene_modes_cnt; i++) {
        printf("supported_scene_modes: [%d] %d\n", i, cap->supported_scene_modes[i]);
    }
    printf("[%lu] supported_aec_modes_cnt: %zu\n", sizeof(cap->supported_aec_modes_cnt), cap->supported_aec_modes_cnt);
    for (int i = 0; i < cap->supported_aec_modes_cnt; i++) {
        printf("supported_aec_modes: [%d] %d\n", i, cap->supported_aec_modes[i]);
    }
    printf("[%lu] fps_ranges_tbl_cnt: %zu\n", sizeof(cap->fps_ranges_tbl_cnt), cap->fps_ranges_tbl_cnt);
    for (int i = 0; i < cap->fps_ranges_tbl_cnt; i++) {
        printf("fps_ranges_tbl: [%d] min_fps: %f, max_fps: %f, video_min_fps: %f, video_max_fps: %f\n", i,
            cap->fps_ranges_tbl[i].min_fps, cap->fps_ranges_tbl[i].max_fps,
            cap->fps_ranges_tbl[i].video_min_fps, cap->fps_ranges_tbl[i].video_max_fps);
    }
    printf("[%lu] supported_antibandings_cnt: %zu\n", sizeof(cap->supported_antibandings_cnt), cap->supported_antibandings_cnt);
    for (int i = 0; i < cap->supported_antibandings_cnt; i++) {
        printf("supported_antibandings: [%d] %d\n", i, cap->supported_antibandings[i]);
    }
    printf("[%lu] supported_white_balances_cnt: %zu\n", sizeof(cap->supported_white_balances_cnt), cap->supported_white_balances_cnt);
    for (int i = 0; i < cap->supported_white_balances_cnt; i++) {
        printf("supported_white_balances: [%d] %d\n", i, cap->supported_white_balances[i]);
    }
    printf("[%lu] supported_sensor_hdr_types_cnt: %zu\n", sizeof(cap->supported_sensor_hdr_types_cnt), cap->supported_sensor_hdr_types_cnt);
    for (int i = 0; i < cap->supported_sensor_hdr_types_cnt; i++) {
        printf("supported_sensor_hdr_types: [%d] %d\n", i, cap->supported_sensor_hdr_types[i]);
    }
    printf("[%lu] min_wb_cct: %d\n", sizeof(cap->min_wb_cct), cap->min_wb_cct);
    printf("[%lu] max_wb_cct: %d\n", sizeof(cap->max_wb_cct), cap->max_wb_cct);
    printf("[%lu] min_wb_gain: %f\n", sizeof(cap->min_wb_gain), cap->min_wb_gain);
    printf("[%lu] max_wb_gain: %f\n", sizeof(cap->max_wb_gain), cap->max_wb_gain);
    printf("[%lu] supported_focus_modes_cnt: %zu\n", sizeof(cap->supported_focus_modes_cnt), cap->supported_focus_modes_cnt);
    for (int i = 0; i < cap->supported_focus_modes_cnt; i++) {
        printf("supported_focus_modes: [%d] %d\n", i, cap->supported_focus_modes[i]);
    }
    for (int i = 0; i < sizeof(cap->min_focus_pos) / sizeof(float); i++) {
        printf("min_focus_pos: [%d] %f\n", i, cap->min_focus_pos[i]);
    }
    for (int i = 0; i < sizeof(cap->max_focus_pos) / sizeof(float); i++) {
        printf("max_focus_pos: [%d] %f\n", i, cap->max_focus_pos[i]);
    }
    printf("[%lu] exposure_compensation_min: %d\n", sizeof(cap->exposure_compensation_min), cap->exposure_compensation_min);
    printf("[%lu] exposure_compensation_max: %d\n", sizeof(cap->exposure_compensation_max), cap->exposure_compensation_max);
    printf("[%lu] exposure_compensation_default: %d\n", sizeof(cap->exposure_compensation_default), cap->exposure_compensation_default);
    printf("[%lu] exposure_compensation_step: %f\n", sizeof(cap->exposure_compensation_step), cap->exposure_compensation_step);
    printf("[%lu] exp_compensation_step:\n", sizeof(cap->exp_compensation_step));
    printf("  numerator: %d\n", cap->exp_compensation_step.numerator);
    printf("  denominator: %d\n", cap->exp_compensation_step.denominator);
    printf("[%lu] video_stablization_supported: %d\n", sizeof(cap->video_stablization_supported), cap->video_stablization_supported);
    printf("[%lu] picture_sizes_tbl_cnt: %zu\n", sizeof(cap->picture_sizes_tbl_cnt), cap->picture_sizes_tbl_cnt);
    for (int i = 0; i < cap->picture_sizes_tbl_cnt; i++) {
        printf("picture_sizes_tbl: [%d] %d x %d\n", i, cap->picture_sizes_tbl[i].width, cap->picture_sizes_tbl[i].height);
    }
    // for (int i = 0; i < sizeof(cap->picture_min_duration) / sizeof(int64_t); i++) {
    //     printf("picture_min_duration: [%d] %d\n", i, cap->picture_min_duration[i]);
    // }
    printf("[%lu] modes_supported: %d\n", sizeof(cap->modes_supported), cap->modes_supported);
    printf("[%lu] sensor_mount_angle: %d\n", sizeof(cap->sensor_mount_angle), cap->sensor_mount_angle);
    printf("[%lu] focal_length: %f\n", sizeof(cap->focal_length), cap->focal_length);
    printf("[%lu] hor_view_angle: %f\n", sizeof(cap->hor_view_angle), cap->hor_view_angle);
    printf("[%lu] ver_view_angle: %f\n", sizeof(cap->ver_view_angle), cap->ver_view_angle);
    // for (int i = 0; i < sizeof(cap->smartisan_reversed1); i++) {
    //     printf("%02x ", cap->smartisan_reversed1[i]);
    // }
    // printf("\n");
    printf("[%lu] preview_sizes_tbl_cnt: %zu\n", sizeof(cap->preview_sizes_tbl_cnt), cap->preview_sizes_tbl_cnt);
    for (int i = 0; i < cap->preview_sizes_tbl_cnt; i++) {
        printf("preview_sizes_tbl: [%d] %d x %d\n", i, cap->preview_sizes_tbl[i].width, cap->preview_sizes_tbl[i].height);
    }
    printf("[%lu] video_sizes_tbl_cnt: %zu\n", sizeof(cap->video_sizes_tbl_cnt), cap->video_sizes_tbl_cnt);
    for (int i = 0; i < cap->video_sizes_tbl_cnt; i++) {
        printf("video_sizes_tbl: [%d] %d x %d\n", i, cap->video_sizes_tbl[i].width, cap->video_sizes_tbl[i].height);
    }
    printf("[%lu] livesnapshot_sizes_tbl_cnt: %zu\n", sizeof(cap->livesnapshot_sizes_tbl_cnt), cap->livesnapshot_sizes_tbl_cnt);
    for (int i = 0; i < cap->livesnapshot_sizes_tbl_cnt; i++) {
        printf("livesnapshot_sizes_tbl: [%d] %d x %d\n", i, cap->livesnapshot_sizes_tbl[i].width, cap->livesnapshot_sizes_tbl[i].height);
    }
    printf("[%lu] vhdr_livesnapshot_sizes_tbl_cnt: %zu\n", sizeof(cap->vhdr_livesnapshot_sizes_tbl_cnt), cap->vhdr_livesnapshot_sizes_tbl_cnt);
    for (int i = 0; i < cap->vhdr_livesnapshot_sizes_tbl_cnt; i++) {
        printf("vhdr_livesnapshot_sizes_tbl: [%d] %d x %d\n", i, cap->vhdr_livesnapshot_sizes_tbl[i].width, cap->vhdr_livesnapshot_sizes_tbl[i].height);
    }
    printf("[%lu] hfr_tbl_cnt: %zu\n", sizeof(cap->hfr_tbl_cnt), cap->hfr_tbl_cnt);
    for (int i = 0; i < cap->hfr_tbl_cnt; i++) {
        printf("hfr_tbl: [%d] mode: %d\n", i, cap->hfr_tbl[i].mode);
    }
    printf("[%lu] zzhdr_sizes_tbl_cnt: %zu\n", sizeof(cap->zzhdr_sizes_tbl_cnt), cap->zzhdr_sizes_tbl_cnt);
    for (int i = 0; i < cap->zzhdr_sizes_tbl_cnt; i++) {
        printf("zzhdr_sizes_tbl: [%d] %d x %d\n", i, cap->zzhdr_sizes_tbl[i].width, cap->zzhdr_sizes_tbl[i].height);
    }
    printf("[%lu] supported_preview_fmt_cnt: %zu\n", sizeof(cap->supported_preview_fmt_cnt), cap->supported_preview_fmt_cnt);
    for (int i = 0; i < cap->supported_preview_fmt_cnt; i++) {
        printf("supported_preview_fmts: [%d] %d\n", i, cap->supported_preview_fmts[i]);
    }
    printf("[%lu] supported_picture_fmt_cnt: %zu\n", sizeof(cap->supported_picture_fmt_cnt), cap->supported_picture_fmt_cnt);
    for (int i = 0; i < cap->supported_picture_fmt_cnt; i++) {
        printf("supported_picture_fmts: [%d] %d\n", i, cap->supported_picture_fmts[i]);
    }
    printf("[%lu] max_downscale_factor: %d\n", sizeof(cap->max_downscale_factor), cap->max_downscale_factor);
    printf("[%lu] supported_raw_dim_cnt: %zu\n", sizeof(cap->supported_raw_dim_cnt), cap->supported_raw_dim_cnt);
    for (int i = 0; i < cap->supported_raw_dim_cnt; i++) {
        printf("raw_dim: [%d] %d x %d\n", i, cap->raw_dim[i].width, cap->raw_dim[i].height);
    }
    printf("[%lu] supported_raw_fmt_cnt: %zu\n", sizeof(cap->supported_raw_fmt_cnt), cap->supported_raw_fmt_cnt);
    for (int i = 0; i < cap->supported_raw_fmt_cnt; i++) {
        printf("supported_raw_fmts: [%d] %d\n", i, cap->supported_raw_fmts[i]);
    }

    printf("[%lu] supported_focus_algos_cnt: %zu\n", sizeof(cap->supported_focus_algos_cnt), cap->supported_focus_algos_cnt);
    for (int i = 0; i < cap->supported_focus_algos_cnt; i++) {
        printf("supported_focus_algos: [%d] %d\n", i, cap->supported_focus_algos[i]);
    }
    printf("[%lu] auto_wb_lock_supported: %d\n", sizeof(cap->auto_wb_lock_supported), cap->auto_wb_lock_supported);
    printf("[%lu] zoom_supported: %d\n", sizeof(cap->zoom_supported), cap->zoom_supported);
    printf("[%lu] smooth_zoom_supported: %d\n", sizeof(cap->smooth_zoom_supported), cap->smooth_zoom_supported);
    printf("[%lu] auto_exposure_lock_supported: %d\n", sizeof(cap->auto_exposure_lock_supported), cap->auto_exposure_lock_supported);
    printf("[%lu] video_snapshot_supported: %d\n", sizeof(cap->video_snapshot_supported), cap->video_snapshot_supported);
    printf("[%lu] max_num_roi: %d\n", sizeof(cap->max_num_roi), cap->max_num_roi);
    printf("[%lu] max_num_focus_areas: %d\n", sizeof(cap->max_num_focus_areas), cap->max_num_focus_areas);
    printf("[%lu] max_num_metering_areas: %d\n", sizeof(cap->max_num_metering_areas), cap->max_num_metering_areas);
    printf("[%lu] max_zoom_step: %d\n", sizeof(cap->max_zoom_step), cap->max_zoom_step);
    printf("[%lu] brightness_ctrl:\n", sizeof(cap->brightness_ctrl));
    printf("  min_value: %lu\n", sizeof(cap->brightness_ctrl.min_value));
    printf("  max_value: %lu\n", sizeof(cap->brightness_ctrl.max_value));
    printf("  def_value: %lu\n", sizeof(cap->brightness_ctrl.def_value));
    printf("  step: %lu\n", sizeof(cap->brightness_ctrl.step));
    printf("[%lu] sharpness_ctrl:\n", sizeof(cap->sharpness_ctrl));
    printf("  min_value: %lu\n", sizeof(cap->sharpness_ctrl.min_value));
    printf("  max_value: %lu\n", sizeof(cap->sharpness_ctrl.max_value));
    printf("  def_value: %lu\n", sizeof(cap->sharpness_ctrl.def_value));
    printf("  step: %lu\n", sizeof(cap->sharpness_ctrl.step));
    printf("[%lu] contrast_ctrl:\n", sizeof(cap->contrast_ctrl));
    printf("  min_value: %lu\n", sizeof(cap->contrast_ctrl.min_value));
    printf("  max_value: %lu\n", sizeof(cap->contrast_ctrl.max_value));
    printf("  def_value: %lu\n", sizeof(cap->contrast_ctrl.def_value));
    printf("  step: %lu\n", sizeof(cap->contrast_ctrl.step));
    printf("[%lu] saturation_ctrl:\n", sizeof(cap->saturation_ctrl));
    printf("  min_value: %lu\n", sizeof(cap->saturation_ctrl.min_value));
    printf("  max_value: %lu\n", sizeof(cap->saturation_ctrl.max_value));
    printf("  def_value: %lu\n", sizeof(cap->saturation_ctrl.def_value));
    printf("  step: %lu\n", sizeof(cap->saturation_ctrl.step));
    printf("[%lu] sce_ctrl:\n", sizeof(cap->sce_ctrl));
    printf("  min_value: %lu\n", sizeof(cap->sce_ctrl.min_value));
    printf("  max_value: %lu\n", sizeof(cap->sce_ctrl.max_value));
    printf("  def_value: %lu\n", sizeof(cap->sce_ctrl.def_value));
    printf("  step: %lu\n", sizeof(cap->sce_ctrl.step));





    printf("[%lu] qcom_supported_feature_mask: %08x\n", sizeof(cap->qcom_supported_feature_mask), cap->qcom_supported_feature_mask);
    printf("[%lu] padding_info:\n", sizeof(cap->padding_info));
    printf("  width_padding: %d\n", sizeof(cap->padding_info.width_padding));
    printf("  height_padding: %d\n", sizeof(cap->padding_info.height_padding));
    printf("  plane_padding: %d\n", sizeof(cap->padding_info.plane_padding));
    printf("  min_stride: %d\n", sizeof(cap->padding_info.min_stride));
    printf("  min_scanline: %d\n", sizeof(cap->padding_info.min_scanline));
    printf("  offset_x: %d\n", sizeof(cap->padding_info.offset_info.offset_x));
    printf("  offset_y: %d\n", sizeof(cap->padding_info.offset_info.offset_y));
    printf("[%lu] min_num_pp_bufs: %d\n", sizeof(cap->min_num_pp_bufs), cap->min_num_pp_bufs);
    printf("[%lu] rdi_mode_stream_fmt: %d\n", sizeof(cap->rdi_mode_stream_fmt), cap->rdi_mode_stream_fmt);
    printf("[%lu] min_focus_distance: %f\n", sizeof(cap->min_focus_distance), cap->min_focus_distance);
    printf("[%lu] hyper_focal_distance: %f\n", sizeof(cap->hyper_focal_distance), cap->hyper_focal_distance);
    for (int i = 0; i < cap->focal_lengths_count; i++) {
        printf("focal_lengths: [%d] %f\n", i, cap->focal_lengths[i]);
    }
    printf("[%lu] focal_lengths_count: %zu\n", sizeof(cap->focal_lengths_count), cap->focal_lengths_count);
    for (int i = 0; i < cap->apertures_count; i++) {
        printf("apertures: [%d] %f\n", i, cap->apertures[i]);
    }
    printf("[%lu] apertures_count: %zu\n", sizeof(cap->apertures_count), cap->apertures_count);
    for (int i = 0; i < cap->filter_densities_count; i++) {
        printf("filter_densities: [%d] %f\n", i, cap->filter_densities[i]);
    }
    printf("[%lu] filter_densities_count: %zu\n", sizeof(cap->filter_densities_count), cap->filter_densities_count);
    for (int i = 0; i < cap->optical_stab_modes_count; i++) {
        printf("optical_stab_modes: [%d] %f\n", i, cap->optical_stab_modes[i]);
    }
    printf("[%lu] optical_stab_modes_count: %zu\n", sizeof(cap->optical_stab_modes_count), cap->optical_stab_modes_count);
    printf("[%lu] lens_shading_map_size: %d x %d\n", sizeof(cap->lens_shading_map_size), cap->lens_shading_map_size.width, cap->lens_shading_map_size.height);
    printf("[%lu] geo_correction_map_size: %d x %d\n", sizeof(cap->geo_correction_map_size), cap->geo_correction_map_size.width, cap->geo_correction_map_size.height);






    printf("[%lu] max_frame_duration: %lu\n", sizeof(cap->max_frame_duration), cap->max_frame_duration);
    printf("[%lu] color_arrangement: %d\n", sizeof(cap->color_arrangement), cap->color_arrangement);
    printf("[%lu] num_color_channels: %d\n", sizeof(cap->num_color_channels), cap->num_color_channels);
    printf("[%lu] gradient_S: %f\n", sizeof(cap->gradient_S), cap->gradient_S);
    printf("[%lu] offset_S: %f\n", sizeof(cap->offset_S), cap->offset_S);
    printf("[%lu] gradient_O: %f\n", sizeof(cap->gradient_O), cap->gradient_O);
    printf("[%lu] offset_O: %f\n", sizeof(cap->offset_O), cap->offset_O);
    for (int i = 0; i < sizeof(cap->sensor_physical_size) / sizeof(float); i++) {
        printf("  sensor_physical_size: [%d] %f\n", i, cap->sensor_physical_size);
    }
    printf("[%lu] pixel_array_size: %d x %d\n", sizeof(cap->pixel_array_size), cap->pixel_array_size.width, cap->pixel_array_size.height);
    printf("[%lu] active_array_size: %d %d %d %d\n", sizeof(cap->active_array_size), cap->active_array_size.left, cap->active_array_size.top, cap->active_array_size.width, cap->active_array_size.height);




    printf("[%lu] supported_ae_modes_cnt: %zu\n", sizeof(cap->supported_ae_modes_cnt), cap->supported_ae_modes_cnt);
    for (int i = 0; i < cap->supported_ae_modes_cnt; i++) {
        printf("supported_ae_modes: [%d] %d\n", i, cap->supported_ae_modes[i]);
    }


    printf("[%lu] scale_picture_sizes_cnt: %zu\n", sizeof(cap->scale_picture_sizes_cnt), cap->scale_picture_sizes_cnt);
    for (int i = 0; i < cap->scale_picture_sizes_cnt; i++) {
        printf("scale_picture_sizes: [%d] %d x %d\n", i, cap->scale_picture_sizes[i].width, cap->scale_picture_sizes[i].height);
    }
    printf("[%lu] flash_available: %d\n", sizeof(cap->flash_available), cap->flash_available);
    printf("[%lu] base_gain_factor:\n", sizeof(cap->base_gain_factor));
    printf("  numerator: %d\n", cap->base_gain_factor.numerator);
    printf("  denominator: %d\n", cap->base_gain_factor.denominator);
    printf("[%lu] ubifocus_af_bracketing_need:\n", sizeof(cap->ubifocus_af_bracketing_need));
    printf("  enable: %d\n", cap->ubifocus_af_bracketing_need.enable);
    printf("  burst_count: %d\n", cap->ubifocus_af_bracketing_need.burst_count);
    printf("  output_count: %d\n", cap->ubifocus_af_bracketing_need.output_count);
    printf("  meta_max_size: %d\n", cap->ubifocus_af_bracketing_need.meta_max_size);
    printf("[%lu] refocus_af_bracketing_need:\n", sizeof(cap->refocus_af_bracketing_need));
    printf("  enable: %d\n", cap->refocus_af_bracketing_need.enable);
    printf("  burst_count: %d\n", cap->refocus_af_bracketing_need.burst_count);
    printf("  output_count: %d\n", cap->refocus_af_bracketing_need.output_count);
    printf("  meta_max_size: %d\n", cap->refocus_af_bracketing_need.meta_max_size);
    printf("[%lu] opti_zoom_settings_need:\n", sizeof(cap->opti_zoom_settings_need));
    printf("  enable: %d\n", cap->opti_zoom_settings_need.enable);
    printf("  burst_count: %d\n", cap->opti_zoom_settings_need.burst_count);
    printf("  zoom_threshold: %d\n", cap->opti_zoom_settings_need.zoom_threshold);
    printf("[%lu] stillmore_settings_need:\n", sizeof(cap->stillmore_settings_need));
    printf("  burst_count: %d\n", cap->stillmore_settings_need.burst_count);
    printf("  min_burst_count: %d\n", cap->stillmore_settings_need.min_burst_count);
    printf("  max_burst_count: %d\n", cap->stillmore_settings_need.max_burst_count);
    printf("[%lu] chroma_flash_settings_need:\n", sizeof(cap->chroma_flash_settings_need));
    printf("  burst_count: %d\n", cap->chroma_flash_settings_need.burst_count);
    printf("  output_count: %d\n", cap->chroma_flash_settings_need.output_count);
    printf("  metadata_index: %d\n", cap->chroma_flash_settings_need.metadata_index);
    printf("[%lu] focus_dist_calibrated: %d\n", sizeof(cap->focus_dist_calibrated), cap->focus_dist_calibrated);
    printf("[%lu] supported_test_pattern_modes_cnt: %zu\n", sizeof(cap->supported_test_pattern_modes_cnt), cap->supported_test_pattern_modes_cnt);
    for (int i = 0; i < cap->supported_test_pattern_modes_cnt; i++) {
        printf("supported_test_pattern_modes: [%d] %d\n", i, cap->supported_test_pattern_modes[i]);
    }
    printf("[%lu] reference_illuminant1: %d\n", sizeof(cap->reference_illuminant1), cap->reference_illuminant1);
    printf("[%lu] reference_illuminant2: %d\n", sizeof(cap->reference_illuminant2), cap->reference_illuminant2);
    for (int i = 0; i < sizeof(cap->jpeg_stall_durations) / sizeof(int64_t); i++) {
        printf("  jpeg_stall_durations: [%d] %lu\n", i, cap->jpeg_stall_durations);
    }
    for (int i = 0; i < sizeof(cap->raw16_stall_durations) / sizeof(int64_t); i++) {
        printf("  raw16_stall_durations: [%d] %lu\n", i, cap->raw16_stall_durations);
    }




    printf("[%lu] isCacSupported: %d\n", sizeof(cap->isCacSupported), cap->isCacSupported);
    printf("[%lu] opaque_raw_fmt: %d\n", sizeof(cap->opaque_raw_fmt), cap->opaque_raw_fmt);
    printf("[%lu] true_portrait_settings_need: %d\n", sizeof(cap->true_portrait_settings_need), cap->true_portrait_settings_need);






    printf("[%lu] sensor_type:\n", sizeof(cap->sensor_type));
    printf("[%lu]   sens_type: %d\n", sizeof(cap->sensor_type.sens_type), cap->sensor_type.sens_type);
    printf("[%lu]   native_format: %d\n", sizeof(cap->sensor_type.native_format), cap->sensor_type.native_format);

    for (int i = 0; i < cap->aberration_modes_count; i++) {
        printf("aberration_modes: [%d] %d\n", i, cap->aberration_modes[i]);
    }
    printf("[%lu] aberration_modes_count: %d\n", sizeof(cap->aberration_modes_count), cap->aberration_modes_count);



    printf("[%lu] max_batch_bufs_supported: %d\n", sizeof(cap->max_batch_bufs_supported), cap->max_batch_bufs_supported);
    printf("[%lu] buf_alignment: %d\n", sizeof(cap->buf_alignment), cap->buf_alignment);
    printf("[%lu] min_stride: %d\n", sizeof(cap->min_stride), cap->min_stride);
    printf("[%lu] min_scanline: %d\n", sizeof(cap->min_scanline), cap->min_scanline);
    printf("[%lu] flash_dev_name: \"%s\"\n", sizeof(cap->flash_dev_name), cap->flash_dev_name);
    printf("[%lu] eeprom_version_info: \"%s\"\n", sizeof(cap->eeprom_version_info), cap->eeprom_version_info);
    printf("[%lu] max_pixel_bandwidth: %llu\n", sizeof(cap->max_pixel_bandwidth), cap->max_pixel_bandwidth);
    printf("[%lu] optical_black_region_count: %d\n", sizeof(cap->optical_black_region_count), cap->optical_black_region_count);
    printf("[%lu] hotPixel_mode: %d\n", sizeof(cap->hotPixel_mode), cap->hotPixel_mode);
    printf("[%lu] hotPixel_count: %d\n", sizeof(cap->hotPixel_count), cap->hotPixel_count);
    printf("[%lu] supported_instant_aec_modes_cnt: %zu\n", sizeof(cap->supported_instant_aec_modes_cnt), cap->supported_instant_aec_modes_cnt);

    printf("--------\n");
    printf("sizeof(cam_capability_t) BLOG: 20320, OSS: %lu\n", sizeof(cam_capability_t));

    free(cap);
    return 0;
}
