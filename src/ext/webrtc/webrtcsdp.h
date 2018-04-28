/* GStreamer
 * Copyright (C) 2017 Matthew Waters <matthew@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __WEBRTC_SDP_H__
#define __WEBRTC_SDP_H__

#include <gst/gst.h>
#include <gst/webrtc/webrtc.h>
#include "fwd.h"

G_BEGIN_DECLS

typedef enum
{
  SDP_NONE,
  SDP_LOCAL,
  SDP_REMOTE,
} SDPSource;

G_GNUC_INTERNAL
const gchar *                       _sdp_source_to_string                   (SDPSource source);


G_GNUC_INTERNAL
gboolean                            validate_sdp                            (GstWebRTCBin * webrtc,
                                                                             SDPSource source,
                                                                             GstWebRTCSessionDescription * sdp,
                                                                             GError ** error);

G_GNUC_INTERNAL
GstWebRTCRTPTransceiverDirection    _get_direction_from_media               (const GstSDPMedia * media);
G_GNUC_INTERNAL
GstWebRTCRTPTransceiverDirection    _intersect_answer_directions            (GstWebRTCRTPTransceiverDirection offer,
                                                                             GstWebRTCRTPTransceiverDirection answer);
G_GNUC_INTERNAL
void                                _media_replace_direction                (GstSDPMedia * media,
                                                                             GstWebRTCRTPTransceiverDirection direction);
G_GNUC_INTERNAL
GstWebRTCRTPTransceiverDirection    _get_final_direction                     (GstWebRTCRTPTransceiverDirection local_dir,
                                                                             GstWebRTCRTPTransceiverDirection remote_dir);

G_GNUC_INTERNAL
GstWebRTCDTLSSetup                  _get_dtls_setup_from_media              (const GstSDPMedia * media);
G_GNUC_INTERNAL
GstWebRTCDTLSSetup                  _intersect_dtls_setup                   (GstWebRTCDTLSSetup offer);
G_GNUC_INTERNAL
void                                _media_replace_setup                    (GstSDPMedia * media,
                                                                             GstWebRTCDTLSSetup setup);
G_GNUC_INTERNAL
GstWebRTCDTLSSetup                  _get_final_setup                        (GstWebRTCDTLSSetup local_setup,
                                                                             GstWebRTCDTLSSetup remote_setup);
G_GNUC_INTERNAL
gchar *                             _generate_fingerprint_from_certificate  (gchar * certificate,
                                                                             GChecksumType checksum_type);
G_GNUC_INTERNAL
void                                _generate_ice_credentials               (gchar ** ufrag,
                                                                             gchar ** password);

G_GNUC_INTERNAL
gboolean                            _media_has_attribute_key                (const GstSDPMedia * media,
                                                                             const gchar * key);


#endif /* __WEBRTC_UTILS_H__ */
