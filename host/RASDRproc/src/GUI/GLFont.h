// -----------------------------------------------------------------------------
// FILE:        "GLFont.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
#ifndef GL_FONT_H
#define GL_FONT_H

#include "GL/glew.h"
#include "GL/gl.h"
#include <string>
#include <vector>

struct GLGlyph
{
    GLGlyph() : id(-1), width(0), height(0), u(0), v(0), offset_x(0), offset_y(0), advance_x(0) {};
    void reset() { id = -1; width=0; height=0; u=0; v=0; offset_x=0, offset_y=0, advance_x=0; bitmap.clear();};
    std::vector<unsigned char> bitmap;
    unsigned short id;
    unsigned short width;
    unsigned short height;
    unsigned short u;
    unsigned short v;
    short offset_x;
    short offset_y;
    short advance_x;
};

class GLFont
{
public:
    GLFont();
    ~GLFont();

    bool load(const char* file);
    bool loadFromArray(const char* array, unsigned int size);
    void render_textWorldSpace(const char *text, float x, float y, float scale, unsigned int rgba = 0x00000000);
    void render_textScreenSpace(const char *text, float x, float y, float scale, unsigned int rgba = 0x00000000);

    unsigned int lineHeight() const;
    unsigned int char_width(const char c) const;
    unsigned int string_width(const char *str) const;

    unsigned int getTextureID() {return m_texID;};

    int m_texwidth;
    int m_texheight;
    GLuint m_texID;
    GLuint m_vboID;
    GLGlyph *m_glyphs;
    const unsigned short m_glyphCount;
    unsigned char m_fontSize;
};

#endif
