#ifndef __STAR_HPP__
#define __STAR_HPP__

#include "iostream"
#include "cstdint"

#include "coor.hpp"


using namespace coor;

class Star
{
    public:
        /** Default constructor */
        Star();
        explicit Star(PolarCoor coor);
        /** Default destructor */
        ~Star();
//        /** Assignment operator
//         *  \param other Object to assign from
//         *  \return A reference to this
//         */
//        Star &operator = (const Star &other);

        /** Access Counter
         * \return The current value of Counter
         */
        unsigned int GetCounter (void) { return Counter; }
        /** Access cartesCoor
         * \return The current value of cartesCoor
         */
//        CartCoor GetcartesCoor (void) { return cartesCoor; }
//        /** Set cartesCoor
//         * \param val New value to set
//         */
//        void SetcartesCoor (CartCoor val) { cartesCoor = val; }
//        /** Access reducedCartesCoor
//         * \return The current value of reducedCartesCoor
//         */
//        ReducedCartCoor GetreducedCartesCoor (void) { return reducedCartesCoor; }
//        /** Set reducedCartesCoor
//         * \param val New value to set
//         */
//        void SetreducedCartesCoor (ReducedCartCoor val) { reducedCartesCoor = val; }
        /** Access polarCoor
         * \return The current value of polarCoor
         */
        PolarCoor getPolarCoor (void) { return polarCoor; }
        /** Set polarCoor
         * \param val New value to set
         */
        void setPolarCoor (PolarCoor val) { polarCoor = val; }


        /*ReducedCartCoor *calculate_ReducedCartCoor (CartCoor coor)
        {
            ReducedCartCoor *reducedCoor;

            //
        }*/

    protected:

    private:
        static unsigned int Counter;                //!< Member variable "Counter"
//        CartCoor cartesCoor;                   //!< Member variable "cartesCoor"
//        ReducedCartCoor reducedCartesCoor;     //!< Member variable "reducedCartesCoor"
        PolarCoor polarCoor;                        //!< Member variable "polarCoor"
};

#endif // __STAR_HPP__
