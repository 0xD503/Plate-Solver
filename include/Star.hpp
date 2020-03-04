#ifndef __STAR_HPP__
#define __STAR_HPP__

#include "iostream"
#include "cstdint"

#include "coor.hpp"


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
//        CartesianCoor GetcartesCoor (void) { return cartesCoor; }
//        /** Set cartesCoor
//         * \param val New value to set
//         */
//        void SetcartesCoor (CartesianCoor val) { cartesCoor = val; }
//        /** Access reducedCartesCoor
//         * \return The current value of reducedCartesCoor
//         */
//        ReducedCartesianCoor GetreducedCartesCoor (void) { return reducedCartesCoor; }
//        /** Set reducedCartesCoor
//         * \param val New value to set
//         */
//        void SetreducedCartesCoor (ReducedCartesianCoor val) { reducedCartesCoor = val; }
        /** Access polarCoor
         * \return The current value of polarCoor
         */
        PolarCoor getPolarCoor (void) { return polarCoor; }
        /** Set polarCoor
         * \param val New value to set
         */
        void setPolarCoor (PolarCoor val) { polarCoor = val; }


        /*ReducedCartesianCoor *calculate_ReducedCartCoor (CartesianCoor coor)
        {
            ReducedCartesianCoor *reducedCoor;

            //
        }*/

    protected:

    private:
        static unsigned int Counter;                //!< Member variable "Counter"
//        CartesianCoor cartesCoor;                   //!< Member variable "cartesCoor"
//        ReducedCartesianCoor reducedCartesCoor;     //!< Member variable "reducedCartesCoor"
        PolarCoor polarCoor;                        //!< Member variable "polarCoor"
};

#endif // __STAR_HPP__
