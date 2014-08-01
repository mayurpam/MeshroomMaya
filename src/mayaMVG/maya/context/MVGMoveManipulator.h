#pragma once

#include "mayaMVG/maya/context/MVGManipulatorUtil.h"
#include <maya/MPxManipulatorNode.h>

namespace mayaMVG {

class MVGMoveManipulator: public MPxManipulatorNode
{	
	enum EMoveState {
        eMoveNone = 0
        , eMovePoint
        , eMoveEdge
    };
	
	public:
		MVGMoveManipulator();
		virtual ~MVGMoveManipulator();
		
	public:
		static void * creator();
		static MStatus initialize();

	public:
		virtual void postConstructor();
		virtual void draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStatus);
		virtual MStatus doPress(M3dView &view);
		virtual MStatus doRelease(M3dView &view);
		virtual MStatus doMove(M3dView &view, bool& refresh);
		virtual MStatus doDrag(M3dView& view);
		virtual void preDrawUI(const M3dView&);
		virtual void drawUI(MHWRender::MUIDrawManager&,	const MHWRender::MFrameContext&) const;

	public:
		void setContext(MVGContext* ctx);
		
	private:
		MPoint updateMouse(M3dView& view, DisplayData* data, short& mousex, short& mousey);
		
		// Draw
		void drawCursor(float mousex, float mousey);
		void drawTriangulateCursor(float mousex, float mousey);
		void drawMoveInPlaneCursor(float mousex, float mousey);
		void drawMoveRecomputePlaneCursor(float mousex, float mousey);
		void drawIntersections(M3dView& view);
			
		// Compute
		void computeTmpFaceOnMovePoint(M3dView& view, DisplayData* data, MPoint& mousePoint, bool recompute=false);
		void computeTmpFaceOnMoveEdge(M3dView& view, DisplayData* data, MPoint& mousePoint, bool recompute=false);
		bool triangulate(M3dView& view, MVGManipulatorUtil::IntersectionData& intersectionData, MPoint& mousePointInCameraCoord, MPoint& resultPoint3D);
		
public:
		static MTypeId _id;
		MVGManipulatorUtil _manipUtils;
		EMoveState _moveState;

};

} // namespace