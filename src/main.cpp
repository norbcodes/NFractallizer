// Norb's Fractallizer by... well, NorbCodes
// Copyright (C) 2025 norbcodes (a.k.a Norb, norb3695)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cstdint>
#include <cmath>
#include <vector>
#include <complex>
#include <thread>
#include <boost/multiprecision/cpp_dec_float.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

typedef boost::multiprecision::cpp_dec_float_100 nfloat;
typedef std::complex<nfloat> ncomplex;

#define FRAME_W 640
#define FRAME_H 360
#define MAX_ITERS 100
#define ESCAPE_BOUNDARY static_cast<nfloat>(2.0)

struct RGB
{
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
};

struct Vector2
{
    nfloat X = 0.0;
    nfloat Y = 0.0;
};

struct Point
{
    nfloat X = 0.0;
    nfloat Y = 0.0;
    RGB Color;
};

RGB Colorize(const ncomplex& C, uint64_t Bounces)
{
    double ClampedBounces = (Bounces > 64) ? 64.0 : static_cast<double>(Bounces);

    return {0, 0, static_cast<uint8_t>(std::floor((ClampedBounces / 64.0) * 255.0))};
}

#define QUARTER     static_cast<nfloat>(1.0/4.0)
#define SIXTEENTH   static_cast<nfloat>(1.0/16.0)

Point CalculatePoint(const nfloat& PX, const nfloat& PY)
{
    ncomplex C(PX, PY);
    ncomplex Z(0.0, 0.0);

    nfloat Q = ((PX - QUARTER) * (PX - QUARTER)) + (PY * PY);

    if ( ((PX + 1) * (PX + 1) + (PY * PY) <= SIXTEENTH) || (Q*(Q+(PX - QUARTER)) <= (PY*PY)*QUARTER) )
    {
        return {PX, PY, {0, 0, 0}};
    }

    for (uint64_t Iter = 0; Iter < MAX_ITERS; Iter++)
    {
        Z = (Z * Z) + C;

        if (boost::multiprecision::abs(Z.real()) > ESCAPE_BOUNDARY || boost::multiprecision::abs(Z.imag()) > ESCAPE_BOUNDARY)
        {
            return {PX, PY, Colorize(C, Iter)};
        }
    }

    return {PX, PY, {0, 0, 0}};
}

void MakeFrame(const Vector2& UCorner, const Vector2& BCorner, std::vector<Point>& PointsList)
{
    // Calculate how much to move on XY axes for each pixel
    nfloat DeltaX = (BCorner.X - UCorner.X) / static_cast<nfloat>(FRAME_W);
    nfloat DeltaY = (BCorner.Y - UCorner.Y) / static_cast<nfloat>(FRAME_H);

    for (uint16_t Y = 0; Y != FRAME_H; Y++)
    {
        for (uint16_t X = 0; X != FRAME_W; X++)
        {
            nfloat PointX = UCorner.X + (DeltaX * static_cast<nfloat>(X + 0));
            nfloat PointY = UCorner.Y + (DeltaY * static_cast<nfloat>(Y + 0));
            PointsList.push_back( CalculatePoint(PointX, PointY) );
        }
    }
}

int main()
{
    nfloat CenterX = -0.75;
    nfloat CenterY = 0.0;
    nfloat ZoomLevel = 3.5;  // Which is basically just the slice of the X axis to render.
    nfloat Height = 1.0;
    Height /= 1.75;
    Height *= ZoomLevel;

    nfloat TopY = (Height / 2.0) + CenterY;
    nfloat BottomY = (-(Height / 2.0)) + CenterY;
    nfloat RightX = (-(ZoomLevel / 2.0)) + CenterX;
    nfloat LeftX = (ZoomLevel / 2.0) + CenterX;

    Vector2 UpperCorner = {RightX, TopY};
    Vector2 BottomCorner = {LeftX, BottomY};

    std::vector<Point> PointsList;

    MakeFrame(UpperCorner, BottomCorner, PointsList);

    RGB* ImageData = new RGB[FRAME_H * FRAME_W];

    for (const Point& P : PointsList)
    {
        nfloat PixelX = (P.X - UpperCorner.X) / (BottomCorner.X - UpperCorner.X) * static_cast<nfloat>(FRAME_W - 1);
        nfloat PixelY = (P.Y - UpperCorner.Y) / (BottomCorner.Y - UpperCorner.Y) * static_cast<nfloat>(FRAME_H - 1);

        uint64_t Y = static_cast<uint64_t>(boost::multiprecision::floor(PixelY));
        uint64_t X = static_cast<uint64_t>(boost::multiprecision::floor(PixelX));
        uint64_t Index = (Y * FRAME_W) + X;

        ImageData[Index].R = P.Color.R;
        ImageData[Index].G = P.Color.G;
        ImageData[Index].B = P.Color.B;
    }

    stbi_write_png("./out.png", FRAME_W, FRAME_H, 3, ImageData, FRAME_W * 3);

    return 0;
}

// Norb's Fractallizer by... well, NorbCodes
// Copyright (C) 2025 norbcodes (a.k.a Norb, norb3695)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.