/**************************************************************************/
/*  visibility_culler_extension.h                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/


#pragma once

#include "core/math/projection.h"
#include "core/math/transform_3d.h"
#include "core/object/gdvirtual.gen.h"
#include "core/object/ref_counted.h"
#include "core/variant/native_ptr.h"

// Lets an extension hide instances that passed Godot's own culling (frustum, layers,
// visibility ranges), for example with its own occlusion culling. Set with
// RenderingServer::set_visibility_culler(). Called on the rendering thread, once per cull pass.
class VisibilityCullerExtension : public RefCounted {
	GDCLASS(VisibilityCullerExtension, RefCounted);

public:
	enum Pass {
		PASS_CAMERA,
		PASS_DIRECTIONAL_SHADOW,
		PASS_POSITIONAL_SHADOW,
	};

protected:
	static void _bind_methods();

	GDVIRTUAL9(_cull, int, RID, RID, int, const Transform3D &, const Projection &, GDExtensionPtr<const real_t>, int, GDExtensionPtr<uint8_t>)

public:
	// p_bounds holds 6 values per instance (world-space min x, y, z then max x, y, z).
	// r_visible starts at 1 for every instance; set an entry to 0 to hide that instance from the pass.
	void cull(Pass p_pass, RID p_viewport, RID p_light, int p_index, const Transform3D &p_transform, const Projection &p_projection, const real_t *p_bounds, uint32_t p_count, uint8_t *r_visible);
};

VARIANT_ENUM_CAST(VisibilityCullerExtension::Pass);
