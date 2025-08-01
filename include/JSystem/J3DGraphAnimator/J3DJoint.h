#ifndef J3DJOINT_H
#define J3DJOINT_H

#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "JSystem/J3DGraphBase/J3DSys.h"

class J3DAnmTransform;
class J3DJoint;
class J3DMaterial;
class J3DMtxBuffer;

/**
 * @ingroup jsystem-j3d
 * 
 */
class J3DMtxCalc {
public:
    /* 80325D1C */ static void setMtxBuffer(J3DMtxBuffer*);

    /* 8000D948 */ virtual ~J3DMtxCalc() {}
    /* 80014E90 */ virtual void setAnmTransform(J3DAnmTransform*) {}
    /* 80014E9C */ virtual J3DAnmTransform* getAnmTransform() { return NULL; }
    /* 80014E8C */ virtual void setAnmTransform(u8, J3DAnmTransform*) {}
    /* 80014E94 */ virtual J3DAnmTransform* getAnmTransform(u8) { return NULL; }
    /* 80014EA4 */ virtual void setWeight(u8, f32) {}
    /* 80014EA8 */ virtual f32 getWeight(u8) const { return 0.0f; }
    virtual void init(const Vec& param_0, const Mtx&) = 0;
    virtual void calc() = 0;

    static J3DMtxBuffer* getMtxBuffer() { return mMtxBuffer; }
    static J3DJoint* getJoint() {
        J3D_ASSERT(185, mJoint != NULL, "Error : null pointer.")
        return mJoint;
    }
    static void setJoint(J3DJoint* joint) { mJoint = joint; }

    static J3DMtxBuffer* mMtxBuffer;
    static J3DJoint* mJoint;
};  // Size: 0x4

typedef int (*J3DJointCallBack)(J3DJoint*, int);

/**
 * @ingroup jsystem-j3d
 * 
 */
class J3DJoint {
public:
    /* 8032F13C */ void appendChild(J3DJoint*);
    /* 8032F170 */ J3DJoint();
    /* 8032F254 */ void entryIn();
    /* 8032F3F8 */ void recursiveCalc();

    J3DMaterial* getMesh() { return mMesh; }
    u16 getJntNo() const { return mJntNo; }
    u8 getScaleCompensate() const { return mScaleCompensate; }
    J3DJoint* getYounger() { return mYounger; }
    void setYounger(J3DJoint* pYounger) { mYounger = pYounger; }
    void setCurrentMtxCalc(J3DMtxCalc* pMtxCalc) { mCurrentMtxCalc = pMtxCalc; }
    J3DTransformInfo& getTransformInfo() { return mTransformInfo; }
    void setTransformInfo(J3DTransformInfo& i_info) { mTransformInfo = i_info; }
    Vec* getMax() { return &mMax; }
    Vec* getMin() { return &mMin; }
    void setCallBack(J3DJointCallBack callback) { mCallBack = callback; }
    J3DJointCallBack getCallBack() { return mCallBack; }
    void setMtxCalc(J3DMtxCalc* i_mtxCalc) { mMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getMtxCalc() { return mMtxCalc; }
    J3DMtxCalc* getCurrentMtxCalc() { return mCurrentMtxCalc; };
    J3DJoint* getChild() { return mChild; }
    u8 getMtxType() { return (mKind & 0xf0) >> 4; }
    void setMtxType(u8 type) { mKind = (mKind & ~0xf0) | (type << 4); }
    f32 getRadius() const { return mBoundingSphereRadius; }

    static J3DMtxCalc* mCurrentMtxCalc;

    inline u8 getKind() { return mKind & 15; }

private:
    friend struct J3DJointFactory;
    friend class J3DJointTree;

    /* 0x00 */ void* mCallBackUserData;
    /* 0x04 */ J3DJointCallBack mCallBack;
    /* 0x08 */ void* field_0x8;
    /* 0x0C */ J3DJoint* mChild;
    /* 0x10 */ J3DJoint* mYounger;
    /* 0x14 */ u16 mJntNo;
    /* 0x16 */ u8 mKind;
    /* 0x17 */ u8 mScaleCompensate;
    /* 0x18 */ J3DTransformInfo mTransformInfo;
    /* 0x38 */ f32 mBoundingSphereRadius;
    /* 0x3C */ Vec mMin;
    /* 0x48 */ Vec mMax;
    /* 0x54 */ J3DMtxCalc* mMtxCalc;
    /* 0x58 */ J3DMaterial* mMesh;
};  // Size: 0x5C

/**
 * @ingroup jsystem-j3d
 * 
 */
class J3DMtxCalcNoAnmBase : public J3DMtxCalc {
public:
    /* 8000FA8C */ virtual ~J3DMtxCalcNoAnmBase() {}
};

/**
 * @ingroup jsystem-j3d
 * 
 */
template <class A, class B>
class J3DMtxCalcNoAnm : public J3DMtxCalcNoAnmBase {
public:
    J3DMtxCalcNoAnm() {}
    virtual ~J3DMtxCalcNoAnm() {}
    virtual void init(const Vec& param_0, const Mtx& param_1) { B::init(param_0, param_1); }
    virtual void calc() { A::calcTransform(mJoint->getTransformInfo()); }
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcJ3DSysInitSoftimage {
    /* 8032ECAC */ static void init(const Vec& param_0, const Mtx& param_1) {
        J3DSys::mCurrentS = param_0;
        MTXCopy(param_1, J3DSys::mCurrentMtx);
    }
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcJ3DSysInitMaya {
    /* 8032ECAC */ static void init(const Vec&, const Mtx& param_1);
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcJ3DSysInitBasic {
    /* 8032EC28 */ static void init(const Vec&, const Mtx& param_1);
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcCalcTransformSoftimage {
    /* 8032EE50 */ static void calcTransform(J3DTransformInfo const&);
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcCalcTransformMaya {
    /* 8032EFBC */ static void calcTransform(J3DTransformInfo const&);
};

/**
 * @ingroup jsystem-j3d
 * 
 */
struct J3DMtxCalcCalcTransformBasic {
    /* 8032ED30 */ static void calcTransform(J3DTransformInfo const&);
};

#endif /* J3DJOINT_H */
