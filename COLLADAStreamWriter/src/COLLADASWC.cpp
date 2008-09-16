/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAStreamWriter.
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWC.h"

namespace COLLADA
{

    const String CSWC::EMPTY_STRING = "";
    const String CSWC::COLLADA_ERR_UNKNOWN_INPUT = "UNKNOWN INPUT ERROR";

    const String CSWC::XML_START_ELEMENT = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
    const String CSWC::COLLADA_NAMESPACE = "http://www.collada.org/2005/11/COLLADASchema";
    const String CSWC::COLLADA_VERSION = "1.4.1";

    const String CSWC::COLLADA_PLATFORM_PC_OGL               = "PC-OGL";
    const String CSWC::COLLADA_PLATFORM_PS3                  = "PS3";
    const String CSWC::COLLADA_PLATFORM_OPENGL_ES            = "OpenGL|ES";
    const String CSWC::COLLADA_PLATFORM_GLES                 = "GLES";
    const String CSWC::COLLADA_PLATFORM_NOKIA_SW             = "NOKIA_SW";

    const String CSWC::COLLADA_PROFILE_COLLADA               = "COLLADA";
    const String CSWC::COLLADA_PROFILE_MAYA                  = "MAYA";
    const String CSWC::COLLADA_PROFILE_CG                    = "CG";
    const String CSWC::COLLADA_PROFILE_GLES                  = "GLES";

    const String CSWC::COLLADA_ELEMENT_ACCESSOR = "accessor";
    const String CSWC::COLLADA_ELEMENT_ALL = "all";
    const String CSWC::COLLADA_ELEMENT_AMBIENT = "ambient";
    const String CSWC::COLLADA_ELEMENT_ANIMATION = "animation";
    const String CSWC::COLLADA_ELEMENT_ANIMATION_CLIP = "animation_clip";
    const String CSWC::COLLADA_ELEMENT_ANNOTATE = "annotate";
    const String CSWC::COLLADA_ELEMENT_ASPECT_RATIO = "aspect_ratio";
    const String CSWC::COLLADA_ELEMENT_ASSET = "asset";
    const String CSWC::COLLADA_ELEMENT_AUTHOR = "author";
    const String CSWC::COLLADA_ELEMENT_AUTHORING_TOOL = "authoring_tool";
    const String CSWC::COLLADA_ELEMENT_BLINN = "blinn";
    const String CSWC::COLLADA_ELEMENT_BIND = "bind";
    const String CSWC::COLLADA_ELEMENT_BIND_MATERIAL = "bind_material";
    const String CSWC::COLLADA_ELEMENT_BIND_SHAPE_MATRIX = "bind_shape_matrix";
    const String CSWC::COLLADA_ELEMENT_BORDER_COLOR = "border_color";
    const String CSWC::COLLADA_ELEMENT_CAMERA = "camera";
    const String CSWC::COLLADA_ELEMENT_CAMERA_ORTHOGRAPHIC = "orthographic";
    const String CSWC::COLLADA_ELEMENT_CAMERA_PERSPECTIVE = "perspective";
    const String CSWC::COLLADA_ELEMENT_CHANNEL = "channel";
    const String CSWC::COLLADA_ELEMENT_CHANNELS = "channels";
    const String CSWC::COLLADA_ELEMENT_CODE = "code";
    const String CSWC::COLLADA_ELEMENT_COMMENTS = "comments";
    const String CSWC::COLLADA_ELEMENT_COMPILER_TARGET = "compiler_target";
    const String CSWC::COLLADA_ELEMENT_COMPILER_OPTIONS = "compiler_options";
    const String CSWC::COLLADA_ELEMENT_CONSTANT = "constant";
	const String CSWC::COLLADA_ELEMENT_CONSTANT_ATTENUATION = "constant_attenuation";
    const String CSWC::COLLADA_ELEMENT_CONTRIBUTOR = "contributor";
    const String CSWC::COLLADA_ELEMENT_CONTROLLER = "controller";
    const String CSWC::COLLADA_ELEMENT_COPYRIGHT = "copyright";
    const String CSWC::COLLADA_ELEMENT_CREATED = "created";
    const String CSWC::COLLADA_ELEMENT_COLLADA = "COLLADA";
    const String CSWC::COLLADA_ELEMENT_COLOR = "color";
    const String CSWC::COLLADA_ELEMENT_COLOR_CLEAR = "color_clear";
    const String CSWC::COLLADA_ELEMENT_COLOR_TARGET = "color_target";
    const String CSWC::COLLADA_ELEMENT_DATA = "data";
    const String CSWC::COLLADA_ELEMENT_DEPTH_CLEAR = "depth_clear";
    const String CSWC::COLLADA_ELEMENT_DEPTH_TARGET = "depth_target";
    const String CSWC::COLLADA_ELEMENT_DIFFUSE = "diffuse";
	const String CSWC::COLLADA_ELEMENT_DIRECTIONAL = "directional";
    const String CSWC::COLLADA_ELEMENT_DRAW = "draw";
    const String CSWC::COLLADA_ELEMENT_EFFECT = "effect";
    const String CSWC::COLLADA_ELEMENT_EMISSION = "emission";
    const String CSWC::COLLADA_ELEMENT_EXTRA = "extra";
    const String CSWC::COLLADA_ELEMENT_FACE = "face";
    const String CSWC::COLLADA_ELEMENT_FALLOFF_ANGLE = "falloff_angle";
    const String CSWC::COLLADA_ELEMENT_FALLOFF_EXPONENT = "falloff_exponent";
    const String CSWC::COLLADA_ELEMENT_FLOAT = "float";
    const String CSWC::COLLADA_ELEMENT_FLOAT_ARRAY = "float_array";
    const String CSWC::COLLADA_ELEMENT_FORMAT = "format";
    const String CSWC::COLLADA_ELEMENT_FORMAT_HINT = "format_hint";
    const String CSWC::COLLADA_ELEMENT_GEOMETRY = "geometry";
    const String CSWC::COLLADA_ELEMENT_H = "h";
    const String CSWC::COLLADA_ELEMENT_IDREF_ARRAY = "IDREF_array";
    const String CSWC::COLLADA_ELEMENT_IMAGE = "image";
    const String CSWC::COLLADA_ELEMENT_INCLUDE = "include";
    const String CSWC::COLLADA_ELEMENT_INDEX_OF_REFRACTION = "index_of_refraction";
    const String CSWC::COLLADA_ELEMENT_INIT_FROM = "init_from";
    const String CSWC::COLLADA_ELEMENT_INIT_AS_TARGET = "init_as_target";
    const String CSWC::COLLADA_ELEMENT_INIT_CUBE = "init_cube";
    const String CSWC::COLLADA_ELEMENT_INIT_VOLUME = "init_volume";
    const String CSWC::COLLADA_ELEMENT_INIT_PLANAR = "init_planar";
    const String CSWC::COLLADA_ELEMENT_INIT_AS_NULL = "init_as_null";
    const String CSWC::COLLADA_ELEMENT_INPUT = "input";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_ANIMATION = "instance_animation";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_CAMERA = "instance_camera";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_CONTROLLER = "instance_controller";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_EFFECT = "instance_effect";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_GEOMETRY = "instance_geometry";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_LIGHT = "instance_light";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_MATERIAL = "instance_material";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_NODE = "instance_node";
    const String CSWC::COLLADA_ELEMENT_INSTANCE_VISUAL_SCENE = "instance_visual_scene";
    const String CSWC::COLLADA_ELEMENT_JOINTS = "joints";
    const String CSWC::COLLADA_ELEMENT_KEYWORDS = "keywords";
    const String CSWC::COLLADA_ELEMENT_LAMBERT = "lambert";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_ANIMATIONS = "library_animations";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_ANIMATION_CLIPS = "library_animation_clips";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_CAMERAS = "library_cameras";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_CONTROLLERS = "library_controllers";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_EFFECTS = "library_effects";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_GEOMETRIES = "library_geometries";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_IMAGES = "library_images";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_LIGHTS = "library_lights";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_MATERIALS = "library_materials";
    const String CSWC::COLLADA_ELEMENT_LIBRARY_VISUAL_SCENES = "library_visual_scenes";
    const String CSWC::COLLADA_ELEMENT_LIGHT = "light";
	const String CSWC::COLLADA_ELEMENT_LINEAR_ATTENUATION = "linear_attenuation";
    const String CSWC::COLLADA_ELEMENT_LOOKAT = "lookat";
    const String CSWC::COLLADA_ELEMENT_MAGFILTER = "magfilter";
    const String CSWC::COLLADA_ELEMENT_MATERIAL = "material";
    const String CSWC::COLLADA_ELEMENT_MATRIX = "matrix";
    const String CSWC::COLLADA_ELEMENT_MESH = "mesh";
    const String CSWC::COLLADA_ELEMENT_MINFILTER = "minfilter";
    const String CSWC::COLLADA_ELEMENT_MIPFILTER = "mipfilter";
    const String CSWC::COLLADA_ELEMENT_MIP_LEVELS = "mip_levels";
    const String CSWC::COLLADA_ELEMENT_MIPMAP_BIAS = "mipmap_bias";
    const String CSWC::COLLADA_ELEMENT_MIPMAP_GENERATE = "mipmap_generate";
    const String CSWC::COLLADA_ELEMENT_MIPMAP_MAXLEVEL = "mipmap_maxlevel";
    const String CSWC::COLLADA_ELEMENT_MODIFIED = "modified";
    const String CSWC::COLLADA_ELEMENT_MODIFIER = "modifier";
    const String CSWC::COLLADA_ELEMENT_MORPH = "morph";
    const String CSWC::COLLADA_ELEMENT_NAME = "name";
    const String CSWC::COLLADA_ELEMENT_NAME_ARRAY = "Name_array";
    const String CSWC::COLLADA_ELEMENT_NEWPARAM = "newparam";
    const String CSWC::COLLADA_ELEMENT_NODE = "node";
    const String CSWC::COLLADA_ELEMENT_OPTICS = "optics";
    const String CSWC::COLLADA_ELEMENT_OPTION = "option";
    const String CSWC::COLLADA_ELEMENT_ORDER = "order";
    const String CSWC::COLLADA_ELEMENT_P = "p";
    const String CSWC::COLLADA_ELEMENT_PARAM = "param";
    const String CSWC::COLLADA_ELEMENT_PASS = "pass";
    const String CSWC::COLLADA_ELEMENT_PH = "ph";
    const String CSWC::COLLADA_ELEMENT_PHONG = "phong";
	const String CSWC::COLLADA_ELEMENT_POINT = "point";
    const String CSWC::COLLADA_ELEMENT_POLYLIST = "polylist";
    const String CSWC::COLLADA_ELEMENT_POLYGONS = "polygons";
    const String CSWC::COLLADA_ELEMENT_PRECISION = "precision";
    const String CSWC::COLLADA_ELEMENT_PRIMARY = "primary";
    const String CSWC::COLLADA_ELEMENT_PROFILE_COMMON = "profile_COMMON";
    const String CSWC::COLLADA_ELEMENT_PROFILE_CG = "profile_CG";
    const String CSWC::COLLADA_ELEMENT_PROFILE_GLES = "profile_GLES";
    const String CSWC::COLLADA_ELEMENT_PROFILE_GLSL = "profile_GLSL";
    const String CSWC::COLLADA_ELEMENT_RANGE = "range";
	const String CSWC::COLLADA_ELEMENT_QUADRATIC_ATTENUATION = "quadratic_attenuation";
    const String CSWC::COLLADA_ELEMENT_REFLECTIVE = "reflective";
    const String CSWC::COLLADA_ELEMENT_REFLECTIVITY = "reflectivity";
    const String CSWC::COLLADA_ELEMENT_REVISION = "revision";
    const String CSWC::COLLADA_ELEMENT_ROTATE = "rotate";
    const String CSWC::COLLADA_ELEMENT_SAMPLER = "sampler";
    const String CSWC::COLLADA_ELEMENT_SAMPLER2D = "sampler2D";
    const String CSWC::COLLADA_ELEMENT_SCALE = "scale";
    const String CSWC::COLLADA_ELEMENT_SCENE = "scene";
    const String CSWC::COLLADA_ELEMENT_SETPARAM = "setparam";
    const String CSWC::COLLADA_ELEMENT_SEMANTIC = "semantic";
    const String CSWC::COLLADA_ELEMENT_SHADER = "shader";
    const String CSWC::COLLADA_ELEMENT_SHININESS = "shininess";
    const String CSWC::COLLADA_ELEMENT_SIZE = "size";
    const String CSWC::COLLADA_ELEMENT_SKELETON = "skeleton";
    const String CSWC::COLLADA_ELEMENT_SKEW = "skew";
    const String CSWC::COLLADA_ELEMENT_SKIN = "skin";
    const String CSWC::COLLADA_ELEMENT_SPECULAR = "specular";
    const String CSWC::COLLADA_ELEMENT_SOURCE = "source";
    const String CSWC::COLLADA_ELEMENT_SOURCE_DATA = "source_data";
	const String CSWC::COLLADA_ELEMENT_SPOT = "spot";
    const String CSWC::COLLADA_ELEMENT_STENCIL_CLEAR = "stencil_clear";
    const String CSWC::COLLADA_ELEMENT_STENCIL_TARGET = "stencil_target";
    const String CSWC::COLLADA_ELEMENT_SUBJECT = "subject";
    const String CSWC::COLLADA_ELEMENT_SURFACE = "surface";
    const String CSWC::COLLADA_ELEMENT_TARGETS = "targets";
    const String CSWC::COLLADA_ELEMENT_TECHNIQUE = "technique";
    const String CSWC::COLLADA_ELEMENT_TECHNIQUE_HINT = "technique_hint";
    const String CSWC::COLLADA_ELEMENT_TECHNIQUE_COMMON = "technique_common";
    const String CSWC::COLLADA_ELEMENT_TEXTURE = "texture";
    const String CSWC::COLLADA_ELEMENT_TITLE = "title";
    const String CSWC::COLLADA_ELEMENT_TRANSLATE = "translate";
    const String CSWC::COLLADA_ELEMENT_TRANSPARENCY = "transparency";
    const String CSWC::COLLADA_ELEMENT_TRANSPARENT = "transparent";
    const String CSWC::COLLADA_ELEMENT_TRIANGLES = "triangles";
    const String CSWC::COLLADA_ELEMENT_UNIT = "unit";
    const String CSWC::COLLADA_ELEMENT_UP_AXIS = "up_axis";
    const String CSWC::COLLADA_ELEMENT_V = "v";
    const String CSWC::COLLADA_ELEMENT_VCOUNT = "vcount";
    const String CSWC::COLLADA_ELEMENT_VERTEX_WEIGHTS = "vertex_weights";
    const String CSWC::COLLADA_ELEMENT_VERTICES = "vertices";
    const String CSWC::COLLADA_ELEMENT_VIEWPORT_RATIO = "viewport_ratio";
    const String CSWC::COLLADA_ELEMENT_VISUAL_SCENE = "visual_scene";
    const String CSWC::COLLADA_ELEMENT_WRAP_S = "wraps";
    const String CSWC::COLLADA_ELEMENT_WRAP_T = "wrapt";
    const String CSWC::COLLADA_ELEMENT_WRAP_P = "wrapp";
    const String CSWC::COLLADA_ELEMENT_XFOV = "xfov";
    const String CSWC::COLLADA_ELEMENT_XMAG = "xmag";
    const String CSWC::COLLADA_ELEMENT_YFOV = "yfov";
    const String CSWC::COLLADA_ELEMENT_YMAG = "ymag";
    const String CSWC::COLLADA_ELEMENT_ZFAR = "zfar";
    const String CSWC::COLLADA_ELEMENT_ZNEAR = "znear";

    const String CSWC::COLLADA_ATTRIBUTE_COUNT = "count";
    const String CSWC::COLLADA_ATTRIBUTE_END = "end";
    const String CSWC::COLLADA_ATTRIBUTE_FACE = "face";
    const String CSWC::COLLADA_ATTRIBUTE_ID = "id";
    const String CSWC::COLLADA_ATTRIBUTE_INDEX = "index";
    const String CSWC::COLLADA_ATTRIBUTE_MATERIAL = "material";
    const String CSWC::COLLADA_ATTRIBUTE_METER = "meter";
    const String CSWC::COLLADA_ATTRIBUTE_METHOD = "method";
    const String CSWC::COLLADA_ATTRIBUTE_MIP = "mip";
    const String CSWC::COLLADA_ATTRIBUTE_NAME = "name";
    const String CSWC::COLLADA_ATTRIBUTE_OFFSET = "offset";
    const String CSWC::COLLADA_ATTRIBUTE_OPAQUE = "opaque";
    const String CSWC::COLLADA_ATTRIBUTE_PLATFORM = "platform";
    const String CSWC::COLLADA_ATTRIBUTE_PROFILE = "profile";
    const String CSWC::COLLADA_ATTRIBUTE_PROGRAM = "program";
    const String CSWC::COLLADA_ATTRIBUTE_REF = "ref";
    const String CSWC::COLLADA_ATTRIBUTE_SEMANTIC = "semantic";
    const String CSWC::COLLADA_ATTRIBUTE_SET = "set";
    const String CSWC::COLLADA_ATTRIBUTE_SID = "sid";
    const String CSWC::COLLADA_ATTRIBUTE_SLICE = "slice";
    const String CSWC::COLLADA_ATTRIBUTE_SOURCE = "source";
    const String CSWC::COLLADA_ATTRIBUTE_STAGE = "stage";
    const String CSWC::COLLADA_ATTRIBUTE_START = "start";
    const String CSWC::COLLADA_ATTRIBUTE_STRIDE = "stride";
    const String CSWC::COLLADA_ATTRIBUTE_SYMBOL = "symbol";
    const String CSWC::COLLADA_ATTRIBUTE_TARGET = "target";
    const String CSWC::COLLADA_ATTRIBUTE_TEXCOORD = "texcoord";
    const String CSWC::COLLADA_ATTRIBUTE_TEXTURE = "texture";
    const String CSWC::COLLADA_ATTRIBUTE_TYPE = "type";
    const String CSWC::COLLADA_ATTRIBUTE_URL = "url";
    const String CSWC::COLLADA_ATTRIBUTE_VALUE = "value";
    const String CSWC::COLLADA_ATTRIBUTE_VERSION = "version";
    const String CSWC::COLLADA_ATTRIBUTE_XMLNS = "xmlns";

    const String CSWC::COLLADA_SEMANTIC_BINDMATRIX = "INV_BIND_MATRIX";
    const String CSWC::COLLADA_SEMANTIC_COLOR = "COLOR";
    const String CSWC::COLLADA_SEMANTIC_CONTINUITY = "CONTINUITY";
    const String CSWC::COLLADA_SEMANTIC_INTERPOLATION = "INTERPOLATION";
    const String CSWC::COLLADA_SEMANTIC_INPUT = "INPUT";
    const String CSWC::COLLADA_SEMANTIC_IN_TANGENT = "IN_TANGENT";
    const String CSWC::COLLADA_SEMANTIC_JOINT = "JOINT";
    const String CSWC::COLLADA_SEMANTIC_LINEAR_STEPS = "LINEAR_STEPS";
    const String CSWC::COLLADA_SEMANTIC_MORPH_WEIGHT = "MORPH_WEIGHT";
    const String CSWC::COLLADA_SEMANTIC_MORPH_TARGET = "MORPH_TARGET";
    const String CSWC::COLLADA_SEMANTIC_NORMAL = "NORMAL";
    const String CSWC::COLLADA_SEMANTIC_OUTPUT = "OUTPUT";
    const String CSWC::COLLADA_SEMANTIC_OUT_TANGENT = "OUT_TANGENT";
    const String CSWC::COLLADA_SEMANTIC_POSITION = "POSITION";
    const String CSWC::COLLADA_SEMANTIC_TEXCOORD = "TEXCOORD";
    const String CSWC::COLLADA_SEMANTIC_VERTEX = "VERTEX";
    const String CSWC::COLLADA_SEMANTIC_WEIGHT = "WEIGHT";

    const String CSWC::COLLADA_TEXT_X_UP = "X_UP";
    const String CSWC::COLLADA_TEXT_Y_UP = "Y_UP";
    const String CSWC::COLLADA_TEXT_Z_UP = "Z_UP";

    const String CSWC::COLLADA_NODE_TYPE_JOINT = "JOINT";
    const String CSWC::COLLADA_NODE_TYPE_NODE = "NODE";

    const String CSWC::COLLADA_VALUE_TYPE_BOOL = "bool";
    const String CSWC::COLLADA_VALUE_TYPE_BOOL2 = "bool2";
    const String CSWC::COLLADA_VALUE_TYPE_BOOL3 = "bool3";
    const String CSWC::COLLADA_VALUE_TYPE_BOOL4 = "bool4";
    const String CSWC::COLLADA_VALUE_TYPE_INT = "int";
    const String CSWC::COLLADA_VALUE_TYPE_INT2 = "int2";
    const String CSWC::COLLADA_VALUE_TYPE_INT3 = "int3";
    const String CSWC::COLLADA_VALUE_TYPE_INT4 = "int4";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT = "float";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT2 = "float2";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT3 = "float3";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT4 = "float4";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT2x2 = "float2x2";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT3x3 = "float3x3";
    const String CSWC::COLLADA_VALUE_TYPE_FLOAT4x4 = "float4x4";
    const String CSWC::COLLADA_VALUE_TYPE_STRING = "string";
    const String CSWC::COLLADA_VALUE_TYPE_SURFACE = "surface";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_1D = "sampler1D";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_2D = "sampler2D";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_3D = "sampler3D";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_CUBE = "samplerCUBE";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_RECT = "samplerRECT";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_DEPTH = "samplerDEPTH";
    const String CSWC::COLLADA_VALUE_TYPE_SAMPLER_STATE = "sampler_state";
    const String CSWC::COLLADA_VALUE_TYPE_NAME = "name";
    const String CSWC::COLLADA_VALUE_TYPE_IDREF = "IDREF";

    const String CSWC::COLLADA_SAMPLER_FILTER_LINEAR = "LINEAR";
    const String CSWC::COLLADA_SAMPLER_FILTER_LINEAR_MIPMAP_LINEAR = "LINEAR_MIPMAP_LINEAR" ;
    const String CSWC::COLLADA_SAMPLER_FILTER_LINEAR_MIPMAP_NEAREST = "LINEAR_MIPMAP_NEAREST";
    const String CSWC::COLLADA_SAMPLER_FILTER_NEAREST = "NEAREST";
    const String CSWC::COLLADA_SAMPLER_FILTER_NEAREST_MIPMAP_NEAREST = "NEAREST_MIPMAP_NEAREST";
    const String CSWC::COLLADA_SAMPLER_FILTER_NEAREST_MIPMAP_LINEAR = "NEAREST_MIPMAP_LINEAR";
    const String CSWC::COLLADA_SAMPLER_FILTER_NONE = "NONE";

    const String CSWC::COLLADA_CHANNEL_RGB = "RGB";
    const String CSWC::COLLADA_CHANNEL_RGBA = "RGBA";
    const String CSWC::COLLADA_CHANNEL_L = "L";
    const String CSWC::COLLADA_CHANNEL_LA = "LA";
    const String CSWC::COLLADA_CHANNEL_D = "D";
    const String CSWC::COLLADA_CHANNEL_XYZ = "XYZ";
    const String CSWC::COLLADA_CHANNEL_XYZW = "XYZW";

    const String CSWC::COLLADA_RANGE_SNORM = "SNORM";
    const String CSWC::COLLADA_RANGE_UNORM = "UNORM";
    const String CSWC::COLLADA_RANGE_SINT = "SINT";
    const String CSWC::COLLADA_RANGE_UINT = "UINT";
    const String CSWC::COLLADA_RANGE_FLOAT = "FLOAT";

    const String CSWC::COLLADA_PRECISION_LOW = "LOW";
    const String CSWC::COLLADA_PRECISION_MID = "MID";
    const String CSWC::COLLADA_PRECISION_HIGH = "HIGH";

    const String CSWC::COLLADA_OPTION_SRGB_GAMMA = "SRGB_GAMMA";
    const String CSWC::COLLADA_OPTION_NORMALIZED3 = "NORMALIZED3";
    const String CSWC::COLLADA_OPTION_NORMALIZED4 = "NORMALIZED4";
    const String CSWC::COLLADA_OPTION_COMPRESSABLE = "COMPRESSABLE";

    // texture wrap modes
    const String CSWC::COLLADA_TEXTURE_WRAP_NONE = "NONE";
    const String CSWC::COLLADA_TEXTURE_WRAP_WRAP = "WRAP";
    const String CSWC::COLLADA_TEXTURE_WRAP_MIRROR = "MIRROR";
    const String CSWC::COLLADA_TEXTURE_WRAP_CLAMP = "CLAMP";
    const String CSWC::COLLADA_TEXTURE_WRAP_BORDER = "BORDER";
    const String CSWC::COLLADA_TEXTURE_WRAP_UNKNOWN = "UNKNOWN";

    const String CSWC::COLLADA_SURFACE_TYPE_UNTYPED = "UNTYPED";
    const String CSWC::COLLADA_SURFACE_TYPE_1D = "1D";
    const String CSWC::COLLADA_SURFACE_TYPE_2D = "2D";
    const String CSWC::COLLADA_SURFACE_TYPE_3D = "3D";
    const String CSWC::COLLADA_SURFACE_TYPE_RECT = "RECT";
    const String CSWC::COLLADA_SURFACE_TYPE_CUBE = "CUBE";
    const String CSWC::COLLADA_SURFACE_TYPE_DEPTH = "DEPTH";


    const String CSWC::COLLADA_OPAQUE_TYPE_A_ONE = "A_ONE";
    const String CSWC::COLLADA_OPAQUE_TYPE_RGB_ONE = "RGB_ONE";
    const String CSWC::COLLADA_OPAQUE_TYPE_RGB_ZERO = "RGB_ZERO";
    const String CSWC::COLLADA_OPAQUE_TYPE_A_ZERO = "A_ZERO";

    const String CSWC::COLLADA_FACE_POSITIVE_X = "POSITIVE_X";
    const String CSWC::COLLADA_FACE_NEGATIVE_X = "NEGATIVE_X";
    const String CSWC::COLLADA_FACE_POSITIVE_Y = "POSITIVE_Y";
    const String CSWC::COLLADA_FACE_NEGATIVE_Y = "NEGATIVE_Y";
    const String CSWC::COLLADA_FACE_POSITIVE_Z = "POSITIVE_Z";
    const String CSWC::COLLADA_FACE_NEGATIVE_Z = "NEGATIVE_Z";

    const String CSWC::COLLADA_MODIFIER_CONST = "CONST";
    const String CSWC::COLLADA_MODIFIER_UNIFORM = "UNIFORM";
    const String CSWC::COLLADA_MODIFIER_VARYING = "VARYING";
    const String CSWC::COLLADA_MODIFIER_STATIC = "STATIC";
    const String CSWC::COLLADA_MODIFIER_VOLATILE = "VOLATILE";
    const String CSWC::COLLADA_MODIFIER_EXTERN = "EXTERN";
    const String CSWC::COLLADA_MODIFIER_SHARED = "SHARED";

    const String CSWC::COLLADA_FX_FUNCTION_NEVER = "NEVER";
    const String CSWC::COLLADA_FX_FUNCTION_LESS = "LESS";
    const String CSWC::COLLADA_FX_FUNCTION_EQUAL = "EQUAL";
    const String CSWC::COLLADA_FX_FUNCTION_LEQUAL = "LEQUAL";
    const String CSWC::COLLADA_FX_FUNCTION_GREATER = "GREATER";
    const String CSWC::COLLADA_FX_FUNCTION_NEQUAL = "NOTEQUAL";
    const String CSWC::COLLADA_FX_FUNCTION_GEQUAL = "GEQUAL";
    const String CSWC::COLLADA_FX_FUNCTION_ALWAYS = "ALWAYS";

    const String CSWC::COLLADA_FX_ANNOTATION_UI_NAME         = "UIName";
    const String CSWC::COLLADA_FX_ANNOTATION_UI_TYPE         = "UIType";
    const String CSWC::COLLADA_FX_ANNOTATION_UI_MIN          = "UIMin";
    const String CSWC::COLLADA_FX_ANNOTATION_UI_MAX          = "UIMax";
    const String CSWC::COLLADA_FX_ANNOTATION_RESOURCE_NAME   = "ResourceName";
    const String CSWC::COLLADA_FX_ANNOTATION_RESOURCE_TYPE   = "ResourceType";
    const String CSWC::COLLADA_FX_UI_TYPE_COLOR              = "color";

}