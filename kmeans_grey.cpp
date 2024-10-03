#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//
#include <iostream>
//
using namespace std ;
using namespace cv  ;
//
//
//
class Obj
{
   private :
      //
      int myValue ;
      int myCount ;
      //
   public :
      //
      Obj()
      {
         myValue = 0 ;
         myCount = 0 ;
      }
      //
      Obj( int value )
      {
         myValue = value ;
         myCount = 0 ;
      }
      //
      ~Obj()
      {
         // called de-structor
      }
      //
      int getValue()
      {
         return myValue ;
      }
      //
      int getCount()
      {
         return myCount ;
      }
      //
      void setValue( int v )
      {
         myValue = v ;
      }
      //
      void setCount( int c )
      {
         myCount = c ;
      }
      //
      int distance( int v )
      {
         int dv = myValue - v ;
         //
         return dv*dv ;
      }
} ;
//
//
//
int main( int argc , char* argv[] ) {
   Mat img ;
   //
   img = imread( "nyc.png" , IMREAD_UNCHANGED ) ;
   //
   cout << img . channels() << endl ;
   //
   //
   //
   const int k = 3;
    RNG rng(1617620);
    unsigned int x = rng.next();
    int limit = x * 255.0 / UINT_MAX;;
   Obj arr[k];
    arr[0].setValue(limit);
    cout << limit << " ";
    x = rng.next();
     limit = x * 255.0 / UINT_MAX;;
    arr[1].setValue(limit);
    cout << limit << " ";
    x = rng.next();
     limit = x * 255.0 / UINT_MAX;;
    arr[2].setValue(limit);
    cout << limit << endl;
    
    int vals[k];
    vals[0] = 0;
    vals[1] = 0;
    vals[2] = 0;
   //
   //
   //
   for(int q = 0; q < 100; q++) {
       vals[0] = 0;
        vals[1] = 0;
        vals[2] = 0;
       for( int r = 0 ; r < img . rows ; r++ )
       {
          for( int c = 0 ; c < img . cols ; c++ )
          {
             int pixel = img . at<uchar> ( r , c ) ;
             //
             int distArr[k];

              int minVal = arr[0].distance(pixel);
              int minK = 0;

              for (int j = 0; j < k; j++) {
                  distArr[j] = arr[j].distance(pixel);

                  if(distArr[j]<minVal) {
                      minVal = distArr[j];
                      minK = j;
                  }
              }
                
              vals[minK] += pixel;
              arr[minK].setCount(arr[minK].getCount() + 1);
          }
       }
        for(int i = 0; i < k; i++) {
            if(arr[i].getCount() == 0) {
                arr[i].setCount(1);
            }
            //cout << arr[i].getCount() << " " << arr[1].getValue() << endl;
            arr[i].setValue((int)(vals[i]/arr[i].getCount()));
            arr[i].setCount(0);
             //cout << arr[i].getValue() << endl;
        }
   }
    
    for( int r = 0 ; r < img . rows ; r++ )
   {
      for( int c = 0 ; c < img . cols ; c++ )
      {
         int pixel = img . at<uchar> ( r , c ) ;
         
          int closestVal = arr[0].distance(pixel);;
          int val = arr[0].getValue();
          
          for(int f = 0; f < k; f++) {
              if (closestVal > arr[f].distance(pixel)) {
                  val = arr[f].getValue();
                  closestVal = arr[f].distance(pixel);
              }
          }
            img . at<uchar> ( r , c ) = val ;
      }
   }
    
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    
    for( int r = 0 ; r < img . rows ; r++ )
   {
      for( int c = 0 ; c < img . cols ; c++ )
      {
         int pixel = img . at<uchar> ( r , c ) ;
         
          if(pixel == arr[0].getValue()) {
              c1 += 1;
          } 
          if(pixel == arr[1].getValue()) {
              c2 += 1;
          }
          if(pixel == arr[2].getValue()) {
              c3 += 1;
          }
      }
   }
    cout << arr[0].getValue() << " " << arr[1].getValue() << " " << arr[2].getValue() << endl;
    c1 = int(100 * c1/(img.rows*img.cols));
    c2 = int(100 * c2/(img.rows*img.cols));
    c3 = int(100 * c3/(img.rows*img.cols));
    cout << c1 << " " << c2 << " " << c3 << endl;
    
   //
   //
   //
   imwrite( "img.png" , img ) ;
   //
   waitKey() ;
   //
   return 0 ;
}
//
// end
//