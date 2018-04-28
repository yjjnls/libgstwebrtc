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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "gstwebrtcbin.h"
#include "utils.h"
#include "webrtctransceiver.h"

#define webrtc_transceiver_parent_class parent_class
G_DEFINE_TYPE (WebRTCTransceiver, webrtc_transceiver,
    GST_TYPE_WEBRTC_RTP_TRANSCEIVER);

enum
{
  PROP_0,
  PROP_WEBRTC,
};

void
webrtc_transceiver_set_transport (WebRTCTransceiver * trans,
    TransportStream * stream)
{
  GstWebRTCRTPTransceiver *rtp_trans;

  g_return_if_fail (WEBRTC_IS_TRANSCEIVER (trans));

  rtp_trans = GST_WEBRTC_RTP_TRANSCEIVER (trans);

  gst_object_replace ((GstObject **) & trans->stream, (GstObject *) stream);

  if (rtp_trans->sender)
    gst_object_replace ((GstObject **) & rtp_trans->sender->transport,
        (GstObject *) stream->transport);
  if (rtp_trans->receiver)
    gst_object_replace ((GstObject **) & rtp_trans->receiver->transport,
        (GstObject *) stream->transport);

  if (rtp_trans->sender)
    gst_object_replace ((GstObject **) & rtp_trans->sender->rtcp_transport,
        (GstObject *) stream->rtcp_transport);
  if (rtp_trans->receiver)
    gst_object_replace ((GstObject **) & rtp_trans->receiver->rtcp_transport,
        (GstObject *) stream->rtcp_transport);
}

static void
webrtc_transceiver_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  WebRTCTransceiver *trans = WEBRTC_TRANSCEIVER (object);

  switch (prop_id) {
    case PROP_WEBRTC:
      gst_object_set_parent (GST_OBJECT (trans), g_value_get_object (value));
      break;
  }

  GST_OBJECT_LOCK (trans);
  switch (prop_id) {
    case PROP_WEBRTC:
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (trans);
}

static void
webrtc_transceiver_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  WebRTCTransceiver *trans = WEBRTC_TRANSCEIVER (object);

  GST_OBJECT_LOCK (trans);
  switch (prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (trans);
}

static void
webrtc_transceiver_finalize (GObject * object)
{
  WebRTCTransceiver *trans = WEBRTC_TRANSCEIVER (object);

  if (trans->stream)
    gst_object_unref (trans->stream);
  trans->stream = NULL;

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
webrtc_transceiver_class_init (WebRTCTransceiverClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->get_property = webrtc_transceiver_get_property;
  gobject_class->set_property = webrtc_transceiver_set_property;
  gobject_class->finalize = webrtc_transceiver_finalize;

  /* some acrobatics are required to set the parent before _constructed()
   * has been called */
  g_object_class_install_property (gobject_class,
      PROP_WEBRTC,
      g_param_spec_object ("webrtc", "Parent webrtcbin",
          "Parent webrtcbin",
          GST_TYPE_WEBRTC_BIN,
          G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS));
}

static void
webrtc_transceiver_init (WebRTCTransceiver * trans)
{
}

WebRTCTransceiver *
webrtc_transceiver_new (GstWebRTCBin * webrtc, GstWebRTCRTPSender * sender,
    GstWebRTCRTPReceiver * receiver)
{
  WebRTCTransceiver *trans;

  trans = g_object_new (webrtc_transceiver_get_type (), "sender", sender,
      "receiver", receiver, "webrtc", webrtc, NULL);

  return trans;
}
