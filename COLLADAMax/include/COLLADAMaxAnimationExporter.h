/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAMax.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    
    Based on the 3dsMax COLLADA Tools:
    Copyright (c) 2005-2006 Autodesk Media Entertainment
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#ifndef __COLLADAMAX_ANIMATIONEXPORTER_H__
#define __COLLADAMAX_ANIMATIONEXPORTER_H__

#include "COLLADAMaxPrerequisites.h"

#include "COLLADAStreamWriter.h"
#include "COLLADALibraryAnimations.h"

#include "COLLADAMaxDocumentExporter.h"
#include "COLLADAMaxConversionFunctor.h"

class Control;

namespace COLLADAMax
{



    /** A class that holds all information needed to export an animation.*/

    class Animation
	    {

    public:
        /** Types of animation*/
        enum Type
        {
            FLOAT,				    //!< Animated float
            FLOAT3,					//!< Animated float3
            FLOAT4,					//!< Animated float4
			FLOAT4x4,				//!< Animated float4x4

            POSITION_X,				//!< Animated x translation
            POSITION_Y,				//!< Animated y translation
            POSITION_Z,				//!< Animated z translation

            ROTATION_X,				//!< Animated x rotation
            ROTATION_Y,				//!< Animated y rotation
            ROTATION_Z,				//!< Animated z rotation

            SCALE_ROT_AXIS,         //!< The pivot rotation for scale/skew
            SCALE_ROT_AXIS_R,       //!< The reverse pivot rotation for scale/skew

            // Collapsed types
            SCALE = FLOAT3,			//!< Animated scale in three dimensions
            TRANSLATION = FLOAT3	//!< Animated translation in three dimensions
        };

		enum InputTypeFlags
		{
			NONE           = 0x0000,
			INPUT          = 0x0001,
			OUTPUT         = 0x0002,
			IN_TANGENT     = 0x0004,
			OUT_TANGENT    = 0x0008,
			INTERPOLATION  = 0x0010
 		};

        /** Function pointer for conversion functions, to convert doubles.*/
    //    typedef float ( *ConversionFunction ) ( const float & );



    private:
        /** The max controller.*/
        Control * mController;

		/** The max node, used for sampled transformations (matrices).*/
		INode * mINode;
		
		/** The id of the element to animate.*/
        String mId;

        /** The sid of the element to animate.*/
        String mSid;

        /** A pointer to an array of parameters to animate.*/
        const String * mParameters;

        /** Type of animation.*/
        int mType;

		/** Flags that indicates which inputs need to be exported in the sampler*/
		int mInputTypeFlags;

        /** Pointer to conversion function, to convert all animated values.*/
        ConversionFunctor* mConversionFunctor;

    public:
        /**
        @param controller the controller used for the animation
        @param id The id of the element to animate
        @param sid The sid of the element to animate
        @param parameter A pointer to an array of parameters to animate
        @param type Type of animation
        @param conversionFunctor Pointer to conversion function, to convert all animated values*/
        Animation ( Control * controller, const String & id, const String & sid, const String * parameter, int type, ConversionFunctor* conversionFunctor = 0 );

		/**Use this constructor to creat an animation for sampled transformation matrices of a max node
		@param nIode the max node which transformation should be animated (sampled)
		@param id The id of the element to animate
		@param sid The sid of the element to animate
		@param parameter A pointer to an array of parameters to animate
		@param type Type of animation
		@param conversionFunctor Pointer to conversion function, to convert all animated values*/
		Animation ( INode * iNode, const String & id, const String & sid, const String * parameter, int type, ConversionFunctor* conversionFunctor = 0 );

		
		/** Destructor*/
		virtual ~Animation();

        /** Returns the controller.*/
        Control * getController() const
        {
            return mController;
        }

		/** Returns the max node.*/
		INode * getNode() const
		{
			return mINode;
		}

		/** Returns the id of the element to animate.*/
        const String & getId() const
        {
            return mId;
        }

        /** Returns the sid of the element to animate.*/
        const String & getSid() const
        {
            return mSid;
        }

        /** Returns the pointer to an array of parameters to animate.*/
        const String * getParameter() const
        {
            return mParameters;
        }

        /** Returns the type of the animation.*/
        int getType() const
        {
            return mType;
        }

        /** Returns the pointer to conversion function, to convert all animated values.*/
        const ConversionFunctor* const & getConversionFunctor() const
        {
            return mConversionFunctor;
        }

        /** Returns the dimension of the animation, i.e. how many values are animated. */
        int getDimension() const;

		/** Sets the input type flags @a newFlags. Previously set flags remain set.*/
		void setInputTypeFlags(int newFlags) { mInputTypeFlags |= newFlags; }

		/** Returns true if the input type flag @a flag is set, false otherwise*/ 
		bool inputFlagSet(InputTypeFlags flag)const { return (mInputTypeFlags & flag) == flag; }

		/** Returns true if at least one input type flag is set.*/
		bool hasAnyInputFlagsSet()const { return mInputTypeFlags != NONE; }
	
		Animation(const Animation& other);
		const Animation& operator=(const Animation& other);

    };


    /** Class to exports all animations of a max document.*/

    class AnimationExporter : public COLLADA::LibraryAnimations
    {

    private:
        /** List of animations*/
        typedef std::vector<Animation> AnimationList;

        /** Function pointer to a function that fills the float buffer @a keyValues with the @a keyIndex'th output value
        of @a animation. */
        typedef void ( AnimationExporter::*OutputValueFunctionPtr ) ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

        /** Function pointer to a function that fills the float buffer @a keyValues with the @a keyIndex'th output value
        of @a animation. */
        typedef void ( AnimationExporter::*TangentValueFunctionPtr ) ( float * tangentValuesX, float * tangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );

        /** Function pointer to a function that returns the interpolation type as a string of @a i'th
        key of @a keyInterface. */
        typedef const String & ( *InterpolationTypeFunctionPtr ) ( IKeyControl * keyInterface, int i );

		/** List of floats used to temporarily store key values.*/
		typedef std::vector<float> KeyValueList;

    private:
		/** Value used for inlength if none is specified.*/
		static const float DEFAULT_INLENGHT;

		/** Value used for outlength if none is specified.*/
		static const float DEFAULT_OUTLENGHT;

		/** Value used for inlength for animated floats if none is specified.*/
		static const float DEFAULT_INLENGHT_FLOAT;

		/** Value used for outlength for animated floats if none is specified.*/
		static const float DEFAULT_OUTLENGHT_FLOAT;

		/** Value used for inlength for animated points if none is specified.*/
		static float DEFAULT_INLENGHT_POINTX_FLOAT_ARRAY[4];

		/** Value used for outlength for animated points if none is specified.*/
		static float DEFAULT_OUTLENGHT_POINTX_FLOAT_ARRAY[4];

        /** The documentexporter this exporter belongs to.*/
        DocumentExporter * mDocumentExporter;

        /** List of all animations to export*/
        AnimationList mAnimationList;

        /** Factor to multiply the key time with to get the real time.*/
        static const float mTimeFactor;

		/** List of floats used to temporarily store key values that need to be calculated and are not stored
		directly in the max api.*/
		KeyValueList mKeyValueList;

		/** Stores the euler angles of the last rotation key, if a rotation that requires patching of the euler 
		angles is being exported*/
		float mPreviousEulerAngles[3];

    public:
        /** Constructor
        @param streamWriter The stream the animation should be written to
        @param documentExporter The documentexporter this exporter belongs to
        */
        AnimationExporter ( COLLADA::StreamWriter * streamWriter, DocumentExporter * documentExporter );

        /** Destructor*/
        ~AnimationExporter()
        {}


        /** Start export of all the animations.*/
        void doExport();

        /** Add @a animation to the list of animations that should be exported.*/
        void addAnimation ( const Animation & animation )
        {
            mAnimationList.push_back ( animation );
        }


		/** Adds an animation that animates a float.
		@param controller The controller that contains the animation.
		@param id The id of the element to animate.
		@param sid The sid of the element to animate.
		@param parameters The parameter list of the element to animate.
		@param conversionFunctor Conversion functor used to convert the output values
		@return Returns true if the float is animated, false otherwise.
		*/
		bool addAnimatedFloat ( Control * controller, const String & id, const String & sid, const String parameters[] = 0, ConversionFunctor* conversionFunctor = 0);


        /** Adds an animation that animates a Point3.
        @param controller The controller that contains the animation
        @param id The id of the element to animate
        @param sid The sid of the element to animate
        @param parameters The parameter list of the element to animate
		@return Returns true if the Point3 is animated, false otherwise.
        */
        bool addAnimatedPoint3 ( Control * controller, const String & id, const String & sid, const String parameters[] = 0, ConversionFunctor* conversionFunctor = 0);

        /** Adds an animation that animates an angle.
        @param controller The controller that contains the animation
        @param id The id of the element to animate
        @param sid The sid of the element to animate
        @param parameters The parameter list of the element to animate
        @param animatedAngle The type of the angle that should be animated
        */
        void addAnimatedAngle ( Control * controller, const String & id, const String & sid, const String parameters[], int animatedAngle );


		void addAnimatedAxisAngle(Control * controller, const String & id, const String & sid, const String parameters[], int type);

		void addAnimatedFloat4x4 ( INode * node, const String & id, const String & sid, const String parameters[] );


		/** Adds an animation that animates a Point3.
        @param controller The controller that contains the animation
        @param id The id of the element to animate
        @param sid The sid of the element to animate
        @param parameters The parameter list of the element to animate
        */
        void addAnimation4 ( Control * controller, const String & id, const String & sid, const String parameters[] );

		bool addAnimatedParameter(IParamBlock * parameterBlock, int parameterId, const String & id, const String & sid, const String parameters[], ConversionFunctor* conversionFunctor = 0  );

		bool addAnimatedParameter(IParamBlock2 * parameterBlock, int parameterId, const String & id, const String & sid, const String parameters[], ConversionFunctor* conversionFunctor = 0  );


        /** Returns true, if the controller is animated an should be exported.*/
        static bool isAnimated ( Control * controller );

		/** Returns true, if the parameter of @a paramBlock with index @a parameterId is animated an should be exported.*/
		static bool isAnimated ( IParamBlock * paramBlock, int parameterId );

		/** Returns true, if the parameter of @a paramBlock with index @a parameterId is animated an should be exported.*/
		static bool isAnimated ( IParamBlock2 * paramBlock, int parameterId );

        /** Generates an id from all the strings contained in @a animation.*/
        static String getBaseId ( const Animation & animation );

        /** Generates the correct target string for use in the @a \<channel\> element.*/
        static String getTarget ( const Animation & animation );

		/** Checks, if the transformations of node @a iNode must be sampled, i.e. it has no stnadart controller*/
		static bool forceSampleMatrices(INode* iNode);




    private:
        /** Disable copy constructor.*/
        AnimationExporter ( const AnimationExporter & animationExporter );

        /** Disable assignment operator.*/
        AnimationExporter & operator= ( const AnimationExporter & animationExporter );


        /** Get the time of the key prior to key number @a i of @a controller.*/
        TimeValue getPreviousTime ( const int & i, Control * controller ) const;

        /** Get the time of the key next to key number @a i of @a controller.*/
        TimeValue getNextTime ( const int & i, const int & keyCount, Control * controller ) const;


		/** Function searches @a controller and all subanims for presence of a Constraint.
		 This is bit of a cheap fix, a slightly better option may be to include
		 parent offset calculation in rotation/position sampling (like Matrix sampling).
		 */
		static bool findConstraint(Animatable* controller);


        /** Exports all the source elements for @a animation.*/
        void exportSources ( Animation & animation );

        /** Exports the input source element.
        @param baseId The base id of the animation
        @param controller The controller being exported
        @param keyInterface The IKeyControl interface*/

        template <class KeyClassName>
        void exportInputSource ( const String & baseId, Control * controller, IKeyControl* keyInterface );


        /** Exports the output source element.
        @param animation The animation being exported
        @param baseId The base id of the animation
        @param keyInterface The IKeyControl interface
        @param outputValueFunction Function pointer to a function used to retrieve the output values*/
        void exportOutputSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, OutputValueFunctionPtr outputValueFunction );

        /** Retrieves the @a keyIndex'th value of type float from @a keyInterface of @a animation and stores it
        in the float buffer @a keyValues.*/
        template <class KeyType>
        void getFloatValue ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

        /** Retrieves the @a keyIndex'th position value of a position animation that animates one value
        from @a keyInterface of @a animation and stores it  in the float buffer @a keyValues. The buffer
        @a keyValues must have at least length 1.*/
		template<class KeyType>
        void getPointXSingleValue ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

        /** Retrieves the three @a keyIndex'th position values of a position animation that animates all
        three values from @a keyInterface of @a animation and stores it in the float buffer @a keyValues.
        The buffer @a keyValues must have at least length 3.*/
		template<int dimension, class KeyType>
        void getPointXValue ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

        /** Retrieves the @a keyIndex'th rotation value of a rotation animation that animates one value
        from @a keyInterface of @a animation and stores it  in the float buffer @a keyValues. The buffer
        @a keyValues must have at least length 1.*/
		template<class KeyType>
        void getRotationSingleValue ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

        /** Retrieves the three @a keyIndex'th rotation values of a rotation animation that animates all
        three values from @a keyInterface of @a animation and stores it in the float buffer @a keyValues.
        The buffer @a keyValues must have at least length 3.*/
		template<class KeyType>
        void getRotationValue ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );


		/** Retrieves the @a keyIndex'th rotation value of a rotation Bezier animation that animates one value
		from @a keyInterface of @a animation and stores it  in the float buffer @a keyValues. The buffer
		@a keyValues must have at least length 1. The value of the key is stored in @a mKeyValueList, for further 
		use by the tangent functions.*/
		void getRotationSingleValuePatchEuler ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );

		/** Retrieves the three @a keyIndex'th rotation values of a rotation Bezier animation that animates one value
		from @a keyInterface of @a animation and stores it  in the float buffer @a keyValues. The buffer
		@a keyValues must have at least length 3. The value of the keys is stored in @a mKeyValueList, for further 
		use by the tangent functions.*/
		void getRotationValuePatchEuler ( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );



		template<class KeyType, bool reversed>
		void getScaleRotationAxisValue( float * keyValues, IKeyControl * keyInterface, const int & keyIndex, const Animation & animation );


        /** Exports a tangent  source element. It can be used for both in and out tangents.
        @param sourceIdSuffix The id suffix that should be used for the  source element
        @param animation The animation being exported
        @param baseId The base id of the animation
        @param keyInterface The IKeyControl interface
        @param tangentValueFunction Function pointer to a function used to retrieve the tangent values*/
        void exportTangentSource ( const String & sourceIdSuffix, const Animation & animation, const String & baseId, IKeyControl* keyInterface, TangentValueFunctionPtr tangentValueFunction );


        /** Exports the in tangent  source element.
        @param animation The animation being exported
        @param baseId The base id of the animation
        @param keyInterface The IKeyControl interface
        @param tangentValueFunction Function pointer to a function used to retrieve the in tangent values*/
        void exportInTangentSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TangentValueFunctionPtr tangentValueFunction );

        /** Retrieves an in tangent value pair of an animated float value.
        @param keyValuesX float array to store the x value
        @param keyValuesY float array to store the y value
        @param keyInterface The IKeyControl interface
        @param keyIndex The index of the key
        @param keyCount The number of keys in the animation
        @param animation The animation to export*/
        void getFloatInTangentValue ( float * keyValuesX, float * keyValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );



		/** Retrieves the @a keyIndex'th position in tangent value pair of a position animation that animates one value
		from @a keyInterface of @a animation and stores them in the float buffers @a inTangentValuesX and @a inTangentValuesY.
		The buffers @a keyValues must have at least length 1.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export
		*/
		template <class KeyType>
		void getPointXSingleInTangentValue ( float * inTangentValuesX, float * inTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves three in tangent values of an animated position or Point3.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		template <int dimension, class KeyType>
		void getPointXInTangentValue ( float * inTangentValuesX, float * inTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves an in tangent value pair of an Bezier animated rotation. It uses @a mKeyValueList to retrieve the
		values of the key. It therefore requires, that @a mKeyValueList has been filled in advance.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		void getRotationSingleInTangentPatchEuler ( float * inTangentValuesX, float * inTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves three in tangent value pairs of an Bezier animated rotation. It uses @a mKeyValueList to retrieve the
		values of the key. It therefore requires, that @a mKeyValueList has been filled in advance.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		void getRotationInTangentPatchEuler ( float * inTangentValuesX, float * inTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


        /** Exports the out tangent  source element.
        @param animation The animation being exported
        @param baseId The base id of the animation
        @param keyInterface The IKeyControl interface
        @param tangentValueFunction Function pointer to a function used to retrieve the out tangent values*/
        void exportOutTangentSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TangentValueFunctionPtr tangentValueFunction );


		/** Retrieves an out tangent value pair of an animated float value.
		@param outTangentValuesX float array to store the x value
		@param outTangentValuesY float array to store the y value
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
        void getFloatOutTangentValue ( float * outTangentValuesX, float * outTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves the @a keyIndex'th position out tangent value pair of a position animation that animates one value
		from @a keyInterface of @a animation and stores them in the float buffers @a inTangentValuesX and @a inTangentValuesY.
		The buffers @a keyValues must have at least length 1.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export
		*/
		template <class KeyType>
		void getPointXSingleOutTangentValue ( float * outTangentValuesX, float * outTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves three out tangent value pair of an animated position or Point3.
		The buffers @a outTangentValuesX and  @a outTangentValuesY must have at least length 3.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		template <int dimension, class KeyType>
		void getPointXOutTangentValue ( float * outTangentValuesX, float * outTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves an in tangent value pair of an Bezier animated rotation. It uses @a mKeyValueList to retrieve the
		values of the key. It therefore requires, that @a mKeyValueList has been filled in advance.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		void getRotationSingleOutTangentPatchEuler ( float * outTangentValuesX, float * outTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );


		/** Retrieves three in tangent value pairs of an Bezier animated rotation. It uses @a mKeyValueList to retrieve the
		values of the key. It therefore requires, that @a mKeyValueList has been filled in advance.
		@param inTangentValuesX float array to store the x values
		@param inTangentValuesY float array to store the y values
		@param keyInterface The IKeyControl interface
		@param keyIndex The index of the key
		@param keyCount The number of keys in the animation
		@param animation The animation to export*/
		void getRotationOutTangentPatchEuler ( float * outTangentValuesX, float * outTangentValuesY, IKeyControl * keyInterface, const int & keyIndex, const int & keyCount, const Animation & animation );



        /** Determines the interpolation type depending on @a flags*/
        static InterpolationType getInterpolationType ( const DWORD & flags );

        /** Exports the interpolation source.
        @param baseId The base id of the animation
        @param keyInterface The IKeyControl interface
        @param interpolationTypeFunction Function pointer to a function used to retrieve the interpolation type
        @param keyCount The number of keys in the animation
        */
        void exportInterpolationSource ( const String & baseId, IKeyControl * keyInterface, InterpolationTypeFunctionPtr interpolationTypeFunction, int keyCount );




		void exportSamplingInputSource ( const String & baseId, TimeValue startTime, TimeValue endTime, int ticksPerFrame );

		
		void exportSamplingFloatOutputSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TimeValue startTime, TimeValue endTime, int ticksPerFrame );

		void exportSamplingPoint3OutputSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TimeValue startTime, TimeValue endTime, int ticksPerFrame );

		void exportSamplingRotationOutputSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TimeValue startTime, TimeValue endTime, int ticksPerFrame );


		void exportSamplingTransformationOutputSource ( const Animation & animation, const String & baseId, IKeyControl* keyInterface, TimeValue startTime, TimeValue endTime, int ticksPerFrame );


		void exportSamplingInterpolationSource ( const String & baseId, TimeValue startTime, TimeValue endTime, int ticksPerFrame );


        /** Returns @a interpolationTypeName for all values of @a keyInterface and keyIndex.*/
        template <const String & interpolationTypeName>
        static const String & getUniformInterpolation ( IKeyControl * keyInterface, int keyIndex );

        /** Returns the type of the interpolation.
        @param keyInterface The IKeyControl interface
        @param keyIndex The number of the key*/
		template <class KeyType>
        static const String & getBezierInterpolation ( IKeyControl * keyInterface, int keyIndex );

        /** Exports the sampler element.*/
        void exportSampler ( const Animation & animation );

        /** Exports the channel element.*/
        void exportChannel ( const Animation & animation );


		/** Approaches the angle @a val to angle @a pval, by adding or subtracting multiples of 2*PI 
		to minimize the absolute value of the distance between them.*/
		void angleApproach(float pval, float& val);

		/** Find the Euler angel representation that is equivalent to the three Euler angles in @a val with
		the smallest distance to @a pval.*/
		void patchEuler(float* pval, float* val);


    };
}

#endif //__COLLADAMAX_ANIMATIONEXPORTER_H__




