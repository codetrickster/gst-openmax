/*
 * Copyright (C) 2007-2009 Nokia Corporation.
 *
 * Author: Felipe Contreras <felipe.contreras@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "gstomx_mpeg4dec.h"
#include "gstomx.h"

GSTOMX_BOILERPLATE (GstOmxMpeg4Dec, gst_omx_mpeg4dec, GstOmxBaseVideoDec,
    GST_OMX_BASE_VIDEODEC_TYPE);

static GstCaps *
generate_sink_template (void)
{
  GstCaps *caps;
  GstStructure *struc;

  caps = gst_caps_new_empty ();

  struc = gst_structure_new ("video/mpeg",
      "mpegversion", G_TYPE_INT, 4,
      "systemstream", G_TYPE_BOOLEAN, FALSE,
      "width", GST_TYPE_INT_RANGE, 16, 4096,
      "height", GST_TYPE_INT_RANGE, 16, 4096,
      "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

  gst_caps_append_structure (caps, struc);

  struc = gst_structure_new ("video/x-divx",
      "divxversion", GST_TYPE_INT_RANGE, 4, 5,
      "width", GST_TYPE_INT_RANGE, 16, 4096,
      "height", GST_TYPE_INT_RANGE, 16, 4096,
      "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

  gst_caps_append_structure (caps, struc);

  struc = gst_structure_new ("video/x-xvid",
      "width", GST_TYPE_INT_RANGE, 16, 4096,
      "height", GST_TYPE_INT_RANGE, 16, 4096,
      "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

  gst_caps_append_structure (caps, struc);

  struc = gst_structure_new ("video/x-3ivx",
      "width", GST_TYPE_INT_RANGE, 16, 4096,
      "height", GST_TYPE_INT_RANGE, 16, 4096,
      "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

  gst_caps_append_structure (caps, struc);

  return caps;
}

static void
type_base_init (gpointer g_class)
{
  GstElementClass *element_class;

  element_class = GST_ELEMENT_CLASS (g_class);

  gst_element_class_set_details_simple (element_class,
      "OpenMAX IL MPEG-4 video decoder",
      "Codec/Decoder/Video",
      "Decodes video in MPEG-4 format with OpenMAX IL", "Felipe Contreras");

  {
    GstPadTemplate *template;

    template = gst_pad_template_new ("sink", GST_PAD_SINK,
        GST_PAD_ALWAYS, generate_sink_template ());

    gst_element_class_add_pad_template (element_class, template);
  }
}

static void
type_class_init (gpointer g_class, gpointer class_data)
{
}

static void
type_instance_init (GTypeInstance * instance, gpointer g_class)
{
  GstOmxBaseVideoDec *omx_base;

  omx_base = GST_OMX_BASE_VIDEODEC (instance);

  omx_base->compression_format = OMX_VIDEO_CodingMPEG4;
}
