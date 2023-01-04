/*
 * Copyright (c) 2020 EKA2L1 Team.
 * 
 * This file is part of EKA2L1 project.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <dispatch/audio.h>
#include <dispatch/camera.h>
#include <dispatch/hui.h>
#include <dispatch/register.h>
#include <dispatch/screen.h>
#include <dispatch/video.h>

#include <dispatch/libraries/sysutils/functions.h>
#include <dispatch/libraries/egl/egl.h>
#include <dispatch/libraries/gles_shared/gles_shared.h>
#include <dispatch/libraries/gles1/gles1.h>
#include <dispatch/libraries/gles2/gles2.h>

namespace eka2l1::dispatch {
    const eka2l1::dispatch::func_map dispatch_funcs = {
        BRIDGE_REGISTER_DISPATCHER(1, update_screen),
        BRIDGE_REGISTER_DISPATCHER(2, fast_blit),
        BRIDGE_REGISTER_DISPATCHER(3, wait_vsync),
        BRIDGE_REGISTER_DISPATCHER(4, cancel_wait_vsync),
        BRIDGE_REGISTER_DISPATCHER(5, flexible_post),
        BRIDGE_REGISTER_DISPATCHER(0x20, eaudio_player_inst),
        BRIDGE_REGISTER_DISPATCHER(0x21, eaudio_player_notify_any_done),
        BRIDGE_REGISTER_DISPATCHER(0x22, eaudio_player_supply_url),
        BRIDGE_REGISTER_DISPATCHER(0x23, eaudio_player_supply_buffer),
        BRIDGE_REGISTER_DISPATCHER(0x24, eaudio_player_set_volume),
        BRIDGE_REGISTER_DISPATCHER(0x25, eaudio_player_get_volume),
        BRIDGE_REGISTER_DISPATCHER(0x26, eaudio_player_max_volume),
        BRIDGE_REGISTER_DISPATCHER(0x27, eaudio_player_play),
        BRIDGE_REGISTER_DISPATCHER(0x28, eaudio_player_stop),
        BRIDGE_REGISTER_DISPATCHER(0x29, eaudio_player_pause),
        BRIDGE_REGISTER_DISPATCHER(0x2A, eaudio_player_cancel_notify_done),
        BRIDGE_REGISTER_DISPATCHER(0x2B, eaudio_player_get_position),
        BRIDGE_REGISTER_DISPATCHER(0x2C, eaudio_player_set_position),
        BRIDGE_REGISTER_DISPATCHER(0x30, eaudio_player_set_repeats),
        BRIDGE_REGISTER_DISPATCHER(0x31, eaudio_player_destroy),
        BRIDGE_REGISTER_DISPATCHER(0x32, eaudio_player_get_dest_sample_rate),
        BRIDGE_REGISTER_DISPATCHER(0x33, eaudio_player_set_dest_sample_rate),
        BRIDGE_REGISTER_DISPATCHER(0x34, eaudio_player_get_dest_channel_count),
        BRIDGE_REGISTER_DISPATCHER(0x35, eaudio_player_set_dest_channel_count),
        BRIDGE_REGISTER_DISPATCHER(0x36, eaudio_player_set_dest_encoding),
        BRIDGE_REGISTER_DISPATCHER(0x37, eaudio_player_get_dest_encoding),
        BRIDGE_REGISTER_DISPATCHER(0x38, eaudio_player_set_dest_container_format),
        BRIDGE_REGISTER_DISPATCHER(0x40, eaudio_dsp_out_stream_create),
        BRIDGE_REGISTER_DISPATCHER(0x41, eaudio_dsp_out_stream_write),
        BRIDGE_REGISTER_DISPATCHER(0x42, eaudio_dsp_stream_set_properties),
        BRIDGE_REGISTER_DISPATCHER(0x43, eaudio_dsp_stream_start),
        BRIDGE_REGISTER_DISPATCHER(0x44, eaudio_dsp_stream_stop),
        BRIDGE_REGISTER_DISPATCHER(0x46, eaudio_dsp_stream_set_format),
        BRIDGE_REGISTER_DISPATCHER(0x47, eaudio_dsp_out_stream_set_volume),
        BRIDGE_REGISTER_DISPATCHER(0x48, eaudio_dsp_out_stream_max_volume),
        BRIDGE_REGISTER_DISPATCHER(0x49, eaudio_dsp_stream_notify_buffer_ready),
        BRIDGE_REGISTER_DISPATCHER(0x4A, eaudio_dsp_in_stream_create),
        BRIDGE_REGISTER_DISPATCHER(0x4B, eaudio_dsp_stream_destroy),
        BRIDGE_REGISTER_DISPATCHER(0x4C, eaudio_dsp_out_stream_volume),
        BRIDGE_REGISTER_DISPATCHER(0x4F, eaudio_dsp_stream_bytes_rendered),
        BRIDGE_REGISTER_DISPATCHER(0x50, eaudio_dsp_stream_position),
        BRIDGE_REGISTER_DISPATCHER(0x52, eaudio_dsp_stream_notify_buffer_ready_cancel),
        BRIDGE_REGISTER_DISPATCHER(0x53, eaudio_dsp_stream_reset_stat),
        BRIDGE_REGISTER_DISPATCHER(0x60, ecam_number_of_cameras),
        BRIDGE_REGISTER_DISPATCHER(0x61, ecam_create),
        BRIDGE_REGISTER_DISPATCHER(0x62, ecam_claim),
        BRIDGE_REGISTER_DISPATCHER(0x63, ecam_release),
        BRIDGE_REGISTER_DISPATCHER(0x64, ecam_power_on),
        BRIDGE_REGISTER_DISPATCHER(0x65, ecam_power_off),
        BRIDGE_REGISTER_DISPATCHER(0x66, ecam_set_parameter),
        BRIDGE_REGISTER_DISPATCHER(0x68, ecam_query_still_image_size),
        BRIDGE_REGISTER_DISPATCHER(0x69, ecam_take_image),
        BRIDGE_REGISTER_DISPATCHER(0x6B, ecam_receive_image),
        BRIDGE_REGISTER_DISPATCHER(0x72, ecam_start_viewfinder),
        BRIDGE_REGISTER_DISPATCHER(0x73, ecam_next_viewfinder_frame),
        BRIDGE_REGISTER_DISPATCHER(0x74, ecam_stop_viewfinder_frame),
        BRIDGE_REGISTER_DISPATCHER(0x80, evideo_player_inst),
        BRIDGE_REGISTER_DISPATCHER(0x81, evideo_player_set_owned_window),
        BRIDGE_REGISTER_DISPATCHER(0x82, evideo_player_set_display_rect),
        BRIDGE_REGISTER_DISPATCHER(0x83, evideo_player_open_file),
        BRIDGE_REGISTER_DISPATCHER(0x85, evideo_player_play),
        BRIDGE_REGISTER_DISPATCHER(0x88, evideo_player_destroy),
        BRIDGE_REGISTER_DISPATCHER(0x8C, evideo_player_set_done_notify),
        BRIDGE_REGISTER_DISPATCHER(0x8D, evideo_player_cancel_done_notify),
        BRIDGE_REGISTER_DISPATCHER(0x8E, evideo_player_close),
        BRIDGE_REGISTER_DISPATCHER(0x92, evideo_player_max_volume),
        BRIDGE_REGISTER_DISPATCHER(0x93, evideo_player_current_volume),
        BRIDGE_REGISTER_DISPATCHER(0x94, evideo_player_set_volume),
        BRIDGE_REGISTER_DISPATCHER(0x95, evideo_player_set_rotation),
        BRIDGE_REGISTER_DISPATCHER(0xA0, ehui_open_input_view),
        BRIDGE_REGISTER_DISPATCHER(0xA1, ehui_get_stored_input_text),
        BRIDGE_REGISTER_DISPATCHER(0xA2, ehui_close_input_view),
        BRIDGE_REGISTER_DISPATCHER(0x1000, sysutils::sysstartup_get_state),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1100, egl_choose_config_emu, "eglChooseConfig"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1101, egl_copy_buffers_emu, "eglCopyBuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1102, egl_create_context_emu, "eglCreateContext"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1103, egl_create_pbuffer_surface_emu, "eglCreatePbufferSurface"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1104, egl_create_pixmap_surface_emu, "eglCreatePixmapSurface"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1105, egl_create_window_surface_emu, "eglCreateWindowSurface"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1106, egl_destroy_context_emu, "eglDestroyContext"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1107, egl_destroy_surface_emu, "eglDestroySurface"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1108, egl_get_config_attrib_emu, "eglGetConfigAttrib"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1109, egl_get_configs_emu, "eglGetConfigs"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110A, egl_get_current_context_emu, "eglGetCurrentContext"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110B, egl_get_current_display_emu, "eglGetCurrentDisplay"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110C, egl_get_current_surface_emu, "eglGetCurrentSurface"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110D, egl_get_display_emu, "eglGetDisplay"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110E, egl_get_error, "eglGetError"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x110F, egl_get_proc_address_emu, "eglGetProcAddress"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1110, egl_initialize_emu, "eglInitialize"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1111, egl_make_current_emu, "eglMakeCurrent"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1112, egl_query_context_emu, "eglQueryContext"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1113, egl_query_string_emu, "eglQueryString"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1114, egl_query_surface_emu, "eglQuerySurface"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1115, egl_swap_buffers_emu, "eglSwapBuffers"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1116, egl_terminate_emu, "eglTerminate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1117, egl_wait_gl_emu, "eglWaitGL"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1118, egl_wait_native_emu, "eglWaitNative"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1119, gl_active_texture_emu, "glActiveTexture"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111A, gl_alpha_func_emu, "glAlphaFunc"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111B, gl_alpha_func_x_emu, "glAlphaFuncx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111C, gl_bind_texture_emu, "glBindTexture"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111D, gl_blend_func_emu, "glBlendFunc"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111E, gl_clear_emu, "glClear"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x111F, gl_clear_color_emu, "glClearColor"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1120, gl_clear_colorx_emu, "glClearColorx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1121, gl_clear_depthf_emu, "glClearDepthf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1122, gl_clear_depthx_emu, "glClearDepthx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1123, gl_clear_stencil, "glClearStencil"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1124, gl_client_active_texture_emu, "glClientActiveTexture"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1125, gl_color_4f_emu, "glColor4f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1126, gl_color_4x_emu, "glColor4x"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1127, gl_color_mask_emu, "glColorMask"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1128, gl_color_pointer_emu, "glColorPointer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1129, gl_compressed_tex_image_2d_emu, "glCompressedTexImage2D"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112A, gl_compressed_tex_sub_image_2d_emu, "glCompressedTexSubImage2D"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112B, gl_copy_tex_image_2d, "glCopyTexImage2D"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112C, gl_copy_tex_sub_image_2d, "glCopyTexSubImage2D"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112D, gl_cull_face_emu, "glCullFace"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112E, gl_delete_textures_emu, "glDeleteTextures"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x112F, gl_depth_func_emu, "glDepthFunc"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1130, gl_depth_mask_emu, "glDepthMask"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1131, gl_depth_rangef_emu, "glDepthRangef"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1132, gl_depth_rangex_emu, "glDepthRangex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1133, gl_disable_emu, "glDisable"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1134, gl_disable_client_state_emu, "glDisableClientState"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1135, gl_draw_arrays_emu, "glDrawArrays"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1136, gl_draw_elements_emu, "glDrawElements"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1137, gl_enable_emu, "glEnable"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1138, gl_enable_client_state_emu, "glEnableClientState"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1139, gl_finish_emu, "glFinish"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113A, gl_flush_emu, "glFlush"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113B, gl_fog_f_emu, "glFogf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113C, gl_fog_fv_emu, "glFogfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113D, gl_fog_x_emu, "glFogx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113E, gl_fog_xv_emu, "glFogxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x113F, gl_front_face_emu, "glFrontFace"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1140, gl_frustumf_emu, "glFurstumf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1141, gl_frustumx_emu, "glFrustumx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1142, gl_gen_textures_emu, "glGenTextures"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1143, gl_get_error_emu, "glGetError"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1144, gl_get_integerv_emu, "glGetIntegerv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1145, gl_get_string_emu, "glGetString"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1146, gl_hint_emu, "glHint"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1147, gl_light_model_f_emu, "glLightModelf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1148, gl_light_model_fv_emu, "glLightModelfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1149, gl_light_model_x_emu, "glLightModelx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114A, gl_light_model_xv_emu, "glLightModelxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114B, gl_light_f_emu, "glLightf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114C, gl_light_fv_emu, "glLightfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114D, gl_light_x_emu, "glLightx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114E, gl_light_xv_emu, "glLightxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x114F, gl_line_width_emu, "glLineWidth"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1150, gl_line_widthx_emu, "glLineWidthx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1151, gl_load_identity_emu, "glLoadIdentity"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1152, gl_load_matrixf_emu, "glLoadMatrixf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1153, gl_load_matrixx_emu, "glLoadMatrixx"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1154, gl_logic_op_emu, "glLogicOp"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1155, gl_material_f_emu, "glMaterialf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1156, gl_material_fv_emu, "glMaterialfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1157, gl_material_x_emu, "glMaterialx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1158, gl_material_xv_emu, "glMaterialxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1159, gl_matrix_mode_emu, "glMatrixMode"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115A, gl_mult_matrixf_emu, "glMultMatrixf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115B, gl_mult_matrixx_emu, "glMultMatrixx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115C, gl_multi_tex_coord_4f_emu, "glMultiTexCoord4f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115D, gl_multi_tex_coord_4x_emu, "glMultiTexCoord4x"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115E, gl_normal_3f_emu, "glNormal3f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x115F, gl_normal_3x_emu, "glNormal3x"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1160, gl_normal_pointer_emu, "glNormalPointer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1161, gl_orthof_emu, "glOrthof"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1162, gl_orthox_emu, "glOrthox"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1163, gl_pixel_storei_emu, "glPixelStorei"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1164, gl_point_size_emu, "glPointSize"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1165, gl_point_sizex_emu, "glPointSizex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1166, gl_polygon_offset_emu, "glPolygonOffset"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1167, gl_polygon_offsetx_emu, "glPolygonOffsetx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1168, gl_pop_matrix_emu, "glPopMatrix"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1169, gl_push_matrix_emu, "glPushMatrix"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116A, gl_query_matrixx_oes_emu, "glQueryMatrixx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116B, gl_read_pixels_emu, "glReadPixels"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116C, gl_rotatef_emu, "glRotatef"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116D, gl_rotatex_emu, "glRotatex"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116E, gl_sample_coverage_emu, "glSampleCoverage"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x116F, gl_sample_coveragex_emu, "glSampleCoveragex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1170, gl_scalef_emu, "glScalef"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1171, gl_scalex_emu, "glScalex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1172, gl_scissor_emu, "glScissor"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1173, gl_shade_model_emu, "glShadeModel"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1174, gl_stencil_func_emu, "glStencilFunc"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1175, gl_stencil_mask_emu, "glStencilMask"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1176, gl_stencil_op_emu, "glStencilOp"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1177, gl_texcoord_pointer_emu, "glTexCoordPointer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1178, gl_tex_envf_emu, "glTexEnvf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1179, gl_tex_envfv_emu, "glTexEnvfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117A, gl_tex_envx_emu, "glTexEnvx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117B, gl_tex_envxv_emu, "glTexEnvxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117C, gl_tex_image_2d_emu, "glTexImage2D"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117D, gl_tex_parameter_f_emu, "glTexParameterf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117E, gl_tex_parameter_x_emu, "glTexParameterx"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x117F, gl_tex_sub_image_2d_emu, "glTexSubImage2D"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1180, gl_translatef_emu, "glTranslatef"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1181, gl_translatex_emu, "glTranslatex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1182, gl_vertex_pointer_emu, "glVertexPointer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1183, gl_viewport_emu, "glViewport"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1184, egl_swap_interval_emu, "eglSwapInterval"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1185, gl_bind_buffer_emu, "glBindBuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1186, gl_buffer_data_emu, "glBufferData"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1187, gl_buffer_sub_data_emu, "glBufferSubData"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1188, gl_clip_plane_f_emu, "glClipPlanef"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1189, gl_clip_plane_x_emu, "glClipPlanex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118A, gl_color_4ub_emu, "glColor4ub"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118B, gl_delete_buffers_emu, "glDeleteBuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118C, gl_gen_buffers_emu, "glGenBuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118D, gl_get_booleanv_emu, "glGetBooleanv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118E, gl_get_buffer_parameter_iv_emu, "glgetBufferParameteriv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x118F, gl_get_clip_plane_f_emu, "glGetClipPlanef"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1190, gl_get_clip_plane_x_emu, "glGetClipPlanex"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1191, gl_get_fixedv_emu, "glGetFixedv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1192, gl_get_floatv_emu, "glGetFloatv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1193, gl_get_light_fv_emu, "glGetLightfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1194, gl_get_light_xv_emu, "glGetLightxv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1195, gl_get_material_fv_emu, "glGetMaterialfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1196, gl_get_material_xv_emu, "glGetMaterialxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1197, gl_get_pointerv_emu, "glGetPointerv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1198, gl_get_tex_env_fv_emu, "glGetTexEnvfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1199, gl_get_tex_env_iv_emu, "glGetTexEnviv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119A, gl_get_tex_env_xv_emu, "glGetTexEnvxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119B, gl_get_tex_parameter_fv_emu, "glGetTexParameterfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119C, gl_get_tex_parameter_iv_emu, "glGetTexParameteriv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119D, gl_get_tex_parameter_xv_emu, "glGetTexParameterxv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119E, gl_is_buffer_emu, "glIsBuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x119F, gl_is_enabled_emu, "glIsEnabled"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A0, gl_is_texture_emu, "glIsTexture"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A1, gl_point_parameter_f_emu, "glPointParameterf"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A2, gl_point_parameter_fv_emu, "glPointParameterfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A3, gl_point_parameter_x_emu, "glPointParameterx"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A4, gl_point_parameter_xv_emu, "glPointParameterxv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A5, gl_point_size_pointer_oes_emu, "glPointSizePointerOES"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A6, gl_tex_envi_emu, "glTexEnvi"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A7, gl_tex_enviv_emu, "glTexEnviv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A8, gl_tex_parameter_fv_emu, "glTexParameterfv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11A9, gl_tex_parameter_i_emu, "glTexParameteri"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AA, gl_tex_parameter_iv_emu, "glTexParameteriv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AB, gl_tex_parameter_xv_emu, "glTexParameterxv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AC, egl_bind_tex_image_emu, "eglBindTexImage"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AD, egl_release_tex_image_emu, "eglReleaseTexImage"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AE, egl_surface_attrib_emu, "eglSurfaceAttrib"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11AF, egl_bind_api_emu, "eglBindAPI"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B0, egl_create_pbuffer_from_client_buffer_emu, "eglCreatePbufferFromClientBuffer"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B1, egl_query_api_emu, "eglQueryAPI"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B2, egl_release_thread_emu, "eglReleaseThread"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B3, egl_wait_client_emu, "eglWaitClient"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B4, gl_current_palette_matrix_oes_emu, "glCurrentPaletteMatrixOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B5, gl_draw_texf_oes_emu, "glDrawTexfOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B6, gl_draw_texfv_oes_emu, "glDrawTexfvOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B7, gl_draw_texi_oes_emu, "glDrawTexiOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B8, gl_draw_texiv_oes_emu, "glDrawTexivOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11B9, gl_draw_texs_oes_emu, "glDrawTexsOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BA, gl_draw_texsv_oes_emu, "glDrawTexsvOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BB, gl_draw_texx_oes_emu, "glDrawTexxOES"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BC, gl_draw_texxv_oes_emu, "glDrawTexxvOES"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BD, gl_load_palette_from_model_view_matrix_oes_emu, "glLoadPaletteFromModelViewMatrixOES"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BE, gl_matrix_index_pointer_oes_emu, "glMatrixIndexPointerOES"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11BF, gl_weight_pointer_oes_emu, "glWeightPointerOES"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C0, gl_attach_shader_emu, "glAttachShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C1, gl_bind_attrib_location_emu, "glBindAttribLocation"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C2, gl_bind_framebuffer_emu, "glBindFramebuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C3, gl_bind_renderbuffer_emu, "glBindRenderbuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C4, gl_blend_color_emu, "glBlendColor"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C5, gl_blend_equation_emu, "glBlendEquation"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C6, gl_blend_equation_separate_emu, "glBlendEquationSeparate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C7, gl_blend_func_separate_emu, "glBlendFuncSeparate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C8, gl_check_framebuffer_status_emu, "glCheckFramebufferStatus"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11C9, gl_compile_shader_emu, "glCompileShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CA, gl_create_program_emu, "glCreateProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CB, gl_create_shader_emu, "glCreateShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CC, gl_delete_framebuffers_emu, "glDeleteFramebuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CD, gl_delete_program_emu, "glDeleteProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CE, gl_delete_renderbuffers_emu, "glDeleteRenderbuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11CF, gl_delete_shader_emu, "glDeleteShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D0, gl_detach_shader_emu, "glDetachShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D1, gl_disable_vertex_attrib_array_emu, "glDisableVertexAttribArray"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D2, gl_enable_vertex_attrib_array_emu, "glEnableVertexAttribArray"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D3, gl_framebuffer_renderbuffer_emu, "glFramebufferRenderbuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D4, gl_framebuffer_texture2d_emu, "glFramebufferTexture2D"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D5, gl_gen_framebuffers_emu, "glGenFramebuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D6, gl_gen_renderbuffers_emu, "glGenRenderbuffers"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D7, gl_generate_mipmap_emu, "glGenerateMipmap"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D8, gl_get_active_attrib_emu, "glGetActiveAttrib"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11D9, gl_get_active_uniform_emu, "glGetActiveUniform"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DA, gl_get_attached_shaders_emu, "glGetAttachedShaders"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DB, gl_get_attrib_location_emu, "glGetAttribLocation"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DC, gl_get_framebuffer_attachment_parameteriv_emu, "glGetFramebufferAttachmentParameteriv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DD, gl_get_program_info_log_emu, "glGetProgramInfoLog"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DE, gl_get_program_iv_emu, "glGetProgramiv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11DF, gl_get_renderbuffer_parameteriv_emu, "glGetRenderbufferParameteriv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E0, gl_get_shader_info_log_emu, "glGetShaderInfoLog"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E1, gl_get_shader_precision_format_emu, "glGetShaderPrecisionFormat"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E2, gl_get_shader_source_emu, "glGetShaderSource"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E3, gl_get_shader_iv_emu, "glGetShaderiv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E4, gl_get_vertex_attrib_pointerv_emu, "glGetVertexAttribPointerv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E5, gl_get_vertex_attrib_fv_emu, "glGetVertexAttribfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E6, gl_get_vertex_attrib_iv_emu, "glGetVertexAttribiv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E7, gl_is_framebuffer_emu, "glIsFramebuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E8, gl_is_program_emu, "glIsProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11E9, gl_is_renderbuffer_emu, "glIsRenderbuffer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11EA, gl_is_shader_emu, "glIsShader"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11EB, gl_link_program_emu, "glLinkProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11EC, gl_release_shader_compiler_emu, "glReleaseShaderCompiler"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11ED, gl_renderbuffer_storage_emu, "glRenderbufferStorage"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11EE, gl_shader_binary_emu, "glShaderBinary"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11EF, gl_shader_source_emu, "glShaderSource"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F0, gl_stencil_func_separate_emu, "glStencilFuncSeparate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F1, gl_stencil_mask_separate_emu, "glStencilMaskSeparate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F2, gl_stencil_op_separate_emu, "glStencilOpSeparate"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F3, gl_uniform_1f_emu, "glUniform1f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F4, gl_uniform_1fv_emu, "glUniform1fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F5, gl_uniform_1i_emu, "glUniform1i"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F6, gl_uniform_1iv_emu, "glUniform1iv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F7, gl_uniform_2f_emu, "glUniform2f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F8, gl_uniform_2fv_emu, "glUniform2fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11F9, gl_uniform_2i_emu, "glUniform2i"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FA, gl_uniform_2iv_emu, "glUniform2iv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FB, gl_uniform_3f_emu, "glUniform3f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FC, gl_uniform_3fv_emu, "glUniform3fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FD, gl_uniform_3i_emu, "glUniform3i"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FE, gl_uniform_3iv_emu, "glUniform3iv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x11FF, gl_uniform_4f_emu, "glUniform4f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1200, gl_uniform_4fv_emu, "glUniform4fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1201, gl_uniform_4i_emu, "glUniform4i"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1202, gl_uniform_4iv_emu, "glUniform4iv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1203, gl_uniform_matrix_2fv_emu, "glUniformMatrix2fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1204, gl_uniform_matrix_3fv_emu, "glUniformMatrix3fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1205, gl_uniform_matrix_4fv_emu, "glUniformMatrix4fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1206, gl_use_program_emu, "glUseProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1207, gl_validate_program_emu, "glValidateProgram"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1208, gl_vertex_attrib_1f_emu, "glVertexAttrib1f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1209, gl_vertex_attrib_1fv_emu, "glVertexAttrib1fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120A, gl_vertex_attrib_2f_emu, "glVertexAttrib2f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120B, gl_vertex_attrib_2fv_emu, "glVertexAttrib2fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120C, gl_vertex_attrib_3f_emu, "glVertexAttrib3f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120D, gl_vertex_attrib_3fv_emu, "glVertexAttrib3fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120E, gl_vertex_attrib_4f_emu, "glVertexAttrib4f"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x120F, gl_vertex_attrib_4fv_emu, "glVertexAttrib4fv"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1210, gl_vertex_attrib_pointer_emu, "glVertexAttribPointer"),
        BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1211, gl_get_uniform_location_emu, "glGetUniformLocation"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1212, gl_get_uniform_fv_emu, "glGetUniformfv"),
        //BRIDGE_REGISTER_DISPATCHER_SYMBOL(0x1213, gl_get_uniform_iv_emu, "glGetUniformiv"),
    };
}