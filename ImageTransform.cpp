#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  
  
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      double center = sqrt((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY)) ;
      double correction = center * 0.005;
      double new_value = pixel.l * (1 - correction);
      
     if (new_value < 0.0 ){
         pixel.l = 0.0;
    } else {  pixel.l = new_value;
  }
      
    }
    
  }

  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  double O = 11.0 ;
  double B = 216.0;
  double O_dist = 0.0;
  double B_dist = 0.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      
      if (abs(pixel.h-O) > 180) {
        O_dist = abs(O+360 - pixel.h);
      } else {
        O_dist = abs(pixel.h - O);
      }
      
      
      if (abs(pixel.h-B) > 180) {
        B_dist = abs(B+360 - pixel.h);
      } else {
        B_dist = abs(pixel.h - B);
      }
      
      if (B_dist > O_dist) {
         pixel.h = O;
      
    } else {
         pixel.h = B;
    }
  }
  }
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  double width_l ;
  double height_l ;
  if (firstImage.width() > secondImage.width()) {
    width_l = secondImage.width() ;
  } else { width_l = firstImage.width();}
    if (firstImage.height() > secondImage.height()) {
    height_l = secondImage.height() ;
  } else { height_l = firstImage.height();}
  
  for (unsigned x = 0; x < width_l; x++) {
    for (unsigned y = 0; y < height_l; y++) {
      HSLAPixel & pixel1 = firstImage.getPixel(x, y);
      HSLAPixel & pixel2 = secondImage.getPixel(x, y);
      
      if (pixel2.l  == 1.0) {
      if (pixel1.l  + 0.2 > 1)  { 
        pixel1.l = 1.0;
      } else {pixel1.l = 0.2 + pixel1.l;
      }
        
      }
    }
  }
  return firstImage;
}
