
// imageProc_20190831View.h: CimageProc20190831View 클래스의 인터페이스
//

#pragma once


class CimageProc20190831View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CimageProc20190831View() noexcept;
	DECLARE_DYNCREATE(CimageProc20190831View)

// 특성입니다.
public:
	CimageProc20190831Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CimageProc20190831View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMenuTest();
//	afx_msg void OnTestMenu();
//	afx_msg void On19();
//	afx_msg void On21();
//	afx_msg void OnTESTBOX();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelStretch();
	afx_msg void OnPixelBinaryzation();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionAverageFilter();
	afx_msg void OnRegionMedian();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinary();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpening();
	afx_msg void OnClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
};

#ifndef _DEBUG  // imageProc_20190831View.cpp의 디버그 버전
inline CimageProc20190831Doc* CimageProc20190831View::GetDocument() const
   { return reinterpret_cast<CimageProc20190831Doc*>(m_pDocument); }
#endif

