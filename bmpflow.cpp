/*
 * bmpflow.cpp
 * Cellular automata based on pixels on the row above
 *
 * Josh Chandler
*/

#ifndef BMPFLOW_CPP
#define BMPFLOW_CPP

#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <string>

#include "EasyBMP_1.06/EasyBMP.h"

using namespace std;
using namespace std::chrono;

bool isWhitePixel(RGBApixel pxl);

int main(int argc, char *argv[])
{
   bool makeframes;
   if (argc > 1 && atoi(argv[1]) == 1) makeframes = true;

   bool rules0[8] = {0, 1, 0, 0, 1, 0, 0, 1};
   bool rules1[8] = {0, 1, 1, 0, 0, 1, 0, 0};
   bool rules2[8] = {0, 0, 1, 0, 1, 0, 1, 0};

   bool *rules;

   int outsize = 128;
   int i,j;
   int rule;
   int random;

   RGBApixel left, mid, right;
   RGBApixel blackpxl = {0, 0, 0, 255};
   RGBApixel redpxl = {64, 0, 0, 255};
   RGBApixel grnpxl = {0, 64, 0, 255};
   RGBApixel blupxl = {0, 0, 64, 255};
   RGBApixel whitepxl = {255, 255, 255, 255};
   RGBApixel *pxl;

   // set random seed
   srand(system_clock::now().time_since_epoch() / milliseconds(1));

   // create output img
   BMP outimg;
   outimg.SetSize(outsize,outsize*2);
   outimg.SetBitDepth(8);

   // make top layer of output img random noise
   for (i=0; i<outimg.TellWidth(); i++)
   {
      if (rand()%2 == 0) // black pixel
      {
         outimg.SetPixel(i,0,blackpxl);
      }
      else
      {
         outimg.SetPixel(i,0,whitepxl);
      }
   }

   // apply rules starting at row 1
   for (j=1; j<outimg.TellHeight(); j++)
   {
      // determine which rule table to use
      random = rand()%3;
      switch (random) {
         case 0:
            rules = rules0;
            pxl = &redpxl;
            break;
         case 1:
            rules = rules1;
            pxl = &grnpxl;
            break;
         case 2:
            rules = rules2;
            pxl = &blupxl;
            break;
      }

      for (i=0; i<outimg.TellWidth(); i++)
      {
         // determine which rule to apply
         rule = 0;
         left = outimg.GetPixel(((i-1)+outsize)%outsize,j-1);
         mid = outimg.GetPixel(i,j-1);
         right = outimg.GetPixel((i+1)%outsize,j-1);

         if (!isWhitePixel(left)) rule += 4;
         if (!isWhitePixel(mid)) rule += 2;
         if (!isWhitePixel(right)) rule += 1;

         // apply rule
         (rules[rule] == true)? outimg.SetPixel(i,j,*pxl):outimg.SetPixel(i,j,whitepxl);
      }

      // output frame
      if (makeframes) outimg.WriteToFile(((string)("frames/" + to_string(j) + ".bmp")).c_str());
   }

   // write
   outimg.WriteToFile("outimg.bmp");

   return 0;
}

bool isWhitePixel(RGBApixel pxl)
{
   if (pxl.Red != 255) return false;
   if (pxl.Green != 255) return false;
   if (pxl.Blue != 255) return false;
   return true;
}

#endif
