
// imageProc_20190831View.cpp: CimageProc20190831View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imageProc_20190831.h"
#endif

#include "imageProc_20190831Doc.h"
#include "imageProc_20190831View.h"
#include "CAngleInputDialog.h"

#include <vfw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimageProc20190831View

IMPLEMENT_DYNCREATE(CimageProc20190831View, CScrollView)

BEGIN_MESSAGE_MAP(CimageProc20190831View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	
//	ON_COMMAND(ID_TESTBOX, &CimageProc20190831View::OnTESTBOX)
    ON_COMMAND(ID_PIXEL_ADD, &CimageProc20190831View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CimageProc20190831View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CimageProc20190831View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CimageProc20190831View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CimageProc20190831View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_STRETCH, &CimageProc20190831View::OnPixelStretch)
	ON_COMMAND(ID_PIXEL_BINARYZATION, &CimageProc20190831View::OnPixelBinaryzation)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CimageProc20190831View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CimageProc20190831View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CimageProc20190831View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CimageProc20190831View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CimageProc20190831View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_SOBEL, &CimageProc20190831View::OnRegionSobel)
	ON_COMMAND(ID_REGION_PREWITT, &CimageProc20190831View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CimageProc20190831View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_AVERAGE_FILTER, &CimageProc20190831View::OnRegionAverageFilter)
	ON_COMMAND(ID_REGION_MEDIAN, &CimageProc20190831View::OnRegionMedian)
	ON_COMMAND(ID_MOPOLOGY_COLOR_TO_GRAY, &CimageProc20190831View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARY, &CimageProc20190831View::OnMopologyBinary)
	ON_COMMAND(ID_EROSION, &CimageProc20190831View::OnErosion)
	ON_COMMAND(ID_DILATION, &CimageProc20190831View::OnDilation)
	ON_COMMAND(ID_OPENING, &CimageProc20190831View::OnOpening)
	ON_COMMAND(ID_CLOSING, &CimageProc20190831View::OnClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CimageProc20190831View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CimageProc20190831View::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SSUBSAMPLING, &CimageProc20190831View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CimageProc20190831View::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEANSUB, &CimageProc20190831View::OnIGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CimageProc20190831View::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CimageProc20190831View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CimageProc20190831View::OnGeometryFilp)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CimageProc20190831View::OnGeometryWarping)
//	ON_WM_RBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_COMMAND(ID_AVI_VIEW, &CimageProc20190831View::OnAviView)
ON_COMMAND(ID_GEOMETRY_MORPHING, &CimageProc20190831View::OnGeometryMorphing)
END_MESSAGE_MAP()

// CimageProc20190831View 생성/소멸

CimageProc20190831View::CimageProc20190831View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bAviMode = false;

}

CimageProc20190831View::~CimageProc20190831View()
{
}

BOOL CimageProc20190831View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CimageProc20190831View 그리기

void CimageProc20190831View::OnDraw(CDC* pDC)
{
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	if (bAviMode) {
	  //avi파일 재생

		loadAviFile(pDC);
		bAviMode = false;
		return;
	}

	if (pDoc->inputImage != NULL) {
		if (pDoc->depth == 1) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->inputImage[y][x],
						pDoc->inputImage[y][x], pDoc->inputImage[y][x]));
				}
			}
		}
		else
			for (int y = 0; y < pDoc->imageHeight; y++)
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImage[y][3 * x + 0],
						pDoc->inputImage[y][3 * x + 1], pDoc->inputImage[y][3 * x + 2]));
			
	}
	if (pDoc->resultImage != NULL) {
		if (pDoc->depth == 1) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x+100+pDoc->imageWidth , y, RGB(pDoc->resultImage[y][x], pDoc->resultImage[y][x],
						pDoc->resultImage[y][x]));
				}
			}
		}
		else
			for(int y = 0; y < pDoc->imageHeight; y++)
			  for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x+100 + pDoc->imageWidth, y, RGB(pDoc->resultImage[y][3 * x + 0],
					pDoc->resultImage[y][3 * x + 1], pDoc->resultImage[y][3 * x + 2]));
	}
	if (pDoc->inputImage2 != NULL) {
		if (pDoc->depth == 1) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + 100 + pDoc->imageWidth+100 + pDoc->imageWidth, y, RGB(pDoc->inputImage2[y][x], 
						pDoc->inputImage2[y][x],pDoc->inputImage2[y][x]));
				}
			}
		}
		else
			for (int y = 0; y < pDoc->imageHeight; y++)
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + 100 + pDoc->imageWidth + 100 + pDoc->imageWidth, y, RGB(pDoc->inputImage2[y][3 * x + 0],
						pDoc->inputImage2[y][3 * x + 1], pDoc->inputImage2[y][3 * x + 2]));
	}

	if (pDoc->gResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, y + pDoc->imageHeight + 20, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, y + pDoc->imageHeight + 20, RGB(pDoc->gResultImg[y][3*x+0], 
						pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
				}
			}
		}
	}
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CimageProc20190831View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CimageProc20190831View 인쇄

BOOL CimageProc20190831View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CimageProc20190831View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CimageProc20190831View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CimageProc20190831View 진단

#ifdef _DEBUG
void CimageProc20190831View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CimageProc20190831View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CimageProc20190831Doc* CimageProc20190831View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimageProc20190831Doc)));
	return (CimageProc20190831Doc*)m_pDocument;
}
#endif //_DEBUG


// CimageProc20190831View 메시지 처리기



//더하기
void CimageProc20190831View::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc= GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL) return;
	pDoc->pixelAdd();
	
	Invalidate(false);
}

//빼기
void CimageProc20190831View::OnPixelSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL) return;
	pDoc->pixelSub();

	Invalidate(false);
}

//곱하기
void CimageProc20190831View::OnPixelMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL) return;
	pDoc->pixelMul();

	Invalidate(false);
}

// 나누기
void CimageProc20190831View::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL) return;
	pDoc->pixelDiv();
	Invalidate(false);
}

//히스토그램 평활화
void CimageProc20190831View::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->pixelHistoEq();
	Invalidate(false);

}

//명암대비 스트레칭
void CimageProc20190831View::OnPixelStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->pixelStretch();
	Invalidate(false);
}

//이진화
void CimageProc20190831View::OnPixelBinaryzation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->pixelBinaryzation();
	Invalidate(false);
}


void CimageProc20190831View::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->pixelTwoImageAdd();
	Invalidate(false);
}


void CimageProc20190831View::OnPixelTwoImageSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->pixelTwoImageSub();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionSharpening();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionSmoothing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionSmoothing();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionEmbossing();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionSobel();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionPrewitt();
	Invalidate(false);
}



void CimageProc20190831View::OnRegionRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionRoberts();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionAverageFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionAverageFilter();
	Invalidate(false);
}


void CimageProc20190831View::OnRegionMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->RegionMedian();
	Invalidate(false);
}


void CimageProc20190831View::OnMopologyColorGray()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MopologyColorGray();
	Invalidate(false);
}


void CimageProc20190831View::OnMopologyBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MopologyBinary();
	Invalidate(false);
}


void CimageProc20190831View::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->Erosion();
	Invalidate(false);
}


void CimageProc20190831View::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->Dilation();
	Invalidate(false);
}


void CimageProc20190831View::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->Opening();
	Invalidate(false);
}


void CimageProc20190831View::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->Closing();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryZoominPixelCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryZoominPixelCopy();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryZoominInterpolation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryZoominInterpolation();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryZoomoutSubsampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryZoomoutSubsampling();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryZoomoutAvg();
	Invalidate(false);
}


void CimageProc20190831View::OnIGeometryZoomoutMeanSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	OnRegionSmoothing();
	pDoc->CopyResultToInput();
	OnGeometryZoomoutSubsampling();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	

	ASSERT_VALID(pDoc);

	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryRotate();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryMirror()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();


	ASSERT_VALID(pDoc);

	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryMirror();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryFilp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryFlip();
	Invalidate(false);
}


void CimageProc20190831View::OnGeometryWarping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImage == NULL)return;
	pDoc->GeometryWarping();
	Invalidate(false);
}


CPoint mPos_start, mPos_end;

void CimageProc20190831View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    mPos_start = point;
	CScrollView::OnLButtonDown(nFlags, point);
	
}


void CimageProc20190831View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	mPos_end = point;

	CDC* pDc = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	pDc->SelectObject(rpen);

	pDc->MoveTo(mPos_start);
	pDc->LineTo(mPos_end);

	ReleaseDC(pDc);

	int Ax, Ay, Bx, By;
	Ax = mPos_start.x;
	Ay = mPos_start.y;
	Bx = mPos_end.x;
	By = mPos_end.y;

	if (Ax < Bx) pDoc->clickStartPx = Ax - (Bx - Ax)/2;
	else pDoc->clickStartPx = Ax + (Ax - Bx) / 2;
	if (Ay < By) pDoc->clickStartPy = Ay - (By - Ay) / 2;
	else pDoc->clickStartPy = Ay + (Ay - By) / 2;
	
	pDoc->clickEndPx = pDoc->clickStartPx;
	pDoc->clickEndPy = pDoc->clickStartPy;

	pDoc->clickStartQx = mPos_start.x;
	pDoc->clickStartQy = mPos_start.y;
	pDoc->clickEndQx = mPos_end.x;
	pDoc->clickEndQy = mPos_end.y;


   	

	CScrollView::OnLButtonUp(nFlags, point);
}


void CimageProc20190831View::OnAviView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file;
	CFileDialog dlg(true,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"AVI파일(*.aiv)|*.avi|모든 파일|*.*|");

	if (dlg.DoModal() == IDOK) {
		AviFileName = dlg.GetPathName();
		bAviMode = true;
		
	}
	Invalidate(false);
}


void CimageProc20190831View::loadAviFile(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi,AviFileName,OF_READ|OF_SHARE_DENY_NONE,NULL);

	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) {
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO) {
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			
			for (frame = 0; frame < si.dwLength; frame++) { 
				pbmih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmih) continue;
				image = (unsigned char*)((LPSTR)pbmih + (WORD)pbmih->biSize);
				/*
				for (int y = 0; y < fi.dwHeight; y++) 
					for (int x = 0; x < fi.dwWidth; x++) {
						pDC->SetPixel(x,fi.dwHeight-1-y,RGB(image[(y*fi.dwWidth+x)*3+2],
							image[(y * fi.dwWidth + x) * 3 + 1], image[(y * fi.dwWidth + x) * 3 + 0]));
					}
				*/

				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight, 0, 0, 0, fi.dwWidth,
					image, (BITMAPINFO*)pbmih, DIB_RGB_COLORS);
				Sleep(30);
			}
		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}


void CimageProc20190831View::OnGeometryMorphing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProc20190831Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->GeometryMorphing();
	Invalidate(false);
}
