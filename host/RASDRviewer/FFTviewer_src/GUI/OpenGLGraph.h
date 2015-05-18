// -----------------------------------------------------------------------------
// FILE: 		OpenGLGraph.h
// DESCRIPTION:	Header for OpenGLGraph.h
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef OPENGL_GRAPH
#define OPENGL_GRAPH



#include "wx/wx.h"
#include "glew/GL/glew.h"
#include "wx/glcanvas.h"

#include <string>
#include <vector>
#include "string.h"
#include <pthread.h>

using namespace std;

enum eOGLGMouseButton
{
	OGLG_LEFT,
	OGLG_RIGHT,
	OGLG_MIDDLE
};

enum eOGLGActionState
{
    OGLG_IDLE,
    OGLG_ZOOMIN,
    OGLG_PAN,
    OGLG_SCALE,
    OGLG_ADD_MARKER,
    OGLG_MOVE_MARKER,
    OGLG_REMOVE_MARKER
};

enum eDrawingMode
{
	GLG_POINTS = 0,
	GLG_LINE
};

template<class T>
struct sRect
{
	sRect(T X1, T X2, T Y1, T Y2)
	{
		x1 = X1;
		x2 = X2;
		y1 = Y1;
		y2 = Y2;
	}
	T x1,x2,y1,y2;
	void set(T X1, T X2, T Y1, T Y2)
	{
		x1 = X1;
		x2 = X2;
		y1 = Y1;
		y2 = Y2;
	}
};

struct GLG_color
{
	GLG_color(unsigned int rgba)
	{
		red = (rgba >> 24)  / 255.0;
		green = ((rgba >> 16) & 0xFF) / 255.0;
		blue = ((rgba >> 8) & 0xFF) / 255.0;
		alpha = (rgba & 0xFF) / 255.0;
	}
	GLG_color() : red(0.5), green(0.5), blue(0.5), alpha(1.0)
	{}

	unsigned int getColor4b()
	{
	    unsigned int color = 0;
	    color |= (unsigned int)(255*red) << 24;
	    color |= (unsigned int)(255*green) << 16;
	    color |= (unsigned int)(255*blue) << 8;
	    color |= (unsigned int)(255*alpha);
	    return color;
	}

	float red;
	float green;
	float blue;
	float alpha;
};

class cDataSerie
{
public:
	cDataSerie() : valuesX(NULL), valuesY(NULL), size(0), allocatedSize(0),
	vboIndex(0), visible(true), modified(true)
	{
		color = 0x000000FF;
		Initialize(1);
	};

	~cDataSerie()
	{
        if(valuesX)
            delete []valuesX;
        if(valuesY)
            delete []valuesY;
	};

	void AssignValues(float *xserie, float *yserie, unsigned int length)
	{
		if(length > allocatedSize && length > 0)
			Initialize(length);
        if(xserie)
            memcpy(valuesX, xserie, (length)*sizeof(float));
		if(yserie)
            memcpy(valuesY, yserie, (length)*sizeof(float));
        modified = true;
        size = length;
	}

	void Clear()
	{

        if(valuesX)
            delete []valuesX;
        if(valuesY)
            delete []valuesY;
		valuesX = NULL;
		valuesY = NULL;
		size = 0;
		allocatedSize = 0;
		modified = true;
	}
	void Initialize(unsigned int length)
	{
		Clear();
		size = length;
		valuesX = new float[size];
		valuesY = new float[size];
		allocatedSize = size;
	}
	void AddXY(float x, float y)
	{
		if(size < allocatedSize)
		{
			valuesX[size] = x;
			valuesY[size] = y;
			++size;
		}
		else
		{
			float *newX = new float [size*2];
			float *newY = new float [size*2];
			allocatedSize = size*2;
			memcpy(newX, valuesX, sizeof(float)*size);
			memcpy(newY, valuesY, sizeof(float)*size);
			delete []valuesX;
			delete []valuesY;
			valuesX = newX;
			valuesY = newY;
			valuesX[size] = x;
			valuesY[size] = y;
			size++;
		}
		modified = true;
	}

	float *valuesX;
	float *valuesY;
	unsigned int size;
	unsigned int allocatedSize;
	unsigned int vboIndex;
	GLG_color color;
	bool visible;
	bool modified;
};

struct GLG_settings
{
	GLG_settings();
	string title;
	string titleXaxis;
	string titleYaxis;

	string xUnits;
	string yUnits;

	bool drawGridX;
	bool drawGridY;
	bool drawTitle;
	bool drawTitleX;
	bool drawTitleY;

	int windowWidth;
	int windowHeight;
	int dataViewWidth;
	int dataViewHeight;

	int marginTop;
	int marginBottom;
	int marginLeft;
	int marginRight;
	int allign;
	bool useVBO;

	GLG_color backgroundColor;
	GLG_color titlesColor;
	GLG_color dataViewBackgroundColor;
	GLG_color dataViewPerimeterColor;
	GLG_color gridColor;
	eDrawingMode graphType;

	sRect<double> visibleArea;

	float gridXstart;
	float gridYstart;
	float gridXspacing;
	float gridYspacing;
	int gridXlines;
	int gridYlines;
	int gridXprec;
	int gridYprec;
	int gridValuesHeight;

	float pointsSize;
	float fontSize;
};

struct OGLMarker
{
	OGLMarker() : color(0xFF0000FF)
	{
		posX = 0;
		posY = 0;
		size = 10;
		iposX = 0;
		iposY = 0;
		dataValueIndex = 0;
    }
	float posX, posY; //data view position
	int iposX, iposY; //window position
	float size;
	GLG_color color;
	int dataValueIndex;
};

class GLFont;

class OpenGLGraph : public wxGLCanvas
{
public:
	OpenGLGraph(wxPanel* parent,  wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name, int* args);
	virtual ~OpenGLGraph();

	void Initialize(int width, int height);
	void Resize(int w, int h);

	void AddSeries();
	void RemoveSeries(unsigned int i);

	void SetInitialDisplayArea(float minx, float maxx, float miny, float maxy);
	void SetDisplayArea(float minx, float maxx, float miny, float maxy);
	void ZoomY( float centerY, float spanY);
	void ZoomX( float centerX, float spanX);
	void Zoom( float centerX, float centerY, float spanX, float spanY);
	void ZoomRect( int x1, int x2, int y1, int y2);
	void Pan( float dx, float dy);

	void SetDrawingMode( eDrawingMode mode );
	void Draw();

	bool SaveConfig(char *file);
	bool LoadConfig(char *file);

	vector<cDataSerie*> series;

	GLG_settings settings;
	void SettingsChanged();

	void OnMouseDown(int mouseButton, int X, int Y);
	void OnMouseUp(int mouseButton, int X, int Y);
	void OnMouseMove(int X, int Y);
	void ResetView();

	void AddMarker(int posX, float size);
	void MoveMarker(int markerID, int posX);
	void RemoveMarker();

	bool markersEnabled;

    char* printUnits(int value, const char *units);
    char m_ctemp[100];

    void setupViewport(int w, int h);
	// events
    void render(wxPaintEvent& evt);
    void resized(wxSizeEvent& evt);
	void mouseMoved(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void leftClick(wxMouseEvent& event);
	void middleClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	DECLARE_EVENT_TABLE()

private:
    wxGLContext *m_DrawingContext;
    wxGLContext *m_emptyContext;
    static float *tempVBObuffer;
	static unsigned int tempVBOsize;
	eOGLGActionState m_actionState;

    bool viewChanged;
	bool initialized;
	sRect<float> initialDisplayArea;
	sRect<int> m_MouseCoord;
	float m_lastSpanX;
	float m_lastSpanY;

	bool isInsideDataView(int X, int Y);
	void dataViewPixelToValue(int x, int y, float &valX, float &valY);

	void DrawStaticElements();
	void DrawMarkers();
	void CalculateGrid();

	void switchToWindowView();
	void switchToDataView();

	void ResizeTempVBO(unsigned int size);

	GLvoid glRenderText(float posx, float posy, float angle, float scale, unsigned int rgba, const char *fmt, ...);
	int TextWidthInPixels(const char *str);
	int NumberWidthInPixels(float num, unsigned int prec = 0);
	int LineHeight();

	float calcAxisGrid(GLG_settings st, bool xAxis);

    GLFont *m_font;

	vector<OGLMarker> markers;
	int m_selectedMarker;
	int m_maxMarkers;
	int clickedOnMarker(int X, int Y);

	GLuint gridVBOid;

	bool m_currentlyDrawing;
	pthread_mutex_t mutex_canDraw;

};

#endif
