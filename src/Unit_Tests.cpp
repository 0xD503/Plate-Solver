#include "../include/Unit_Tests.hpp"


int testCoor (unsigned int x_1, unsigned int y_1, int xr_1, int yr_1,
              double r_1, double phi_1)
{
    CartesianCoor           *cCoor_1 = new CartesianCoor;
    ReducedCartesianCoor    *rcCoor_1 = new ReducedCartesianCoor, *result_1 = new ReducedCartesianCoor;
    PolarCoor               *pCoor_1 = new PolarCoor, *result_2 = new PolarCoor;

    *cCoor_1 = {x_1, y_1};
    *rcCoor_1 = {xr_1, yr_1};
    *pCoor_1 = {r_1, phi_1};

    result_1 = calculateReducedCoor(cCoor_1, 400, 200);
    result_2 = calculatePolarCoor(result_1);
    cout << "Reduced cCoor_1: {" << result_1->x_Reduced << ", " << result_1->y_Reduced << "}" << endl;
    cout << "Transformed result_1: {" << result_2->r << ", " << result_2->phi << "}" << endl;
    cout << "Rad to deg: " << radToDeg(result_2->phi) << endl << endl;

    *cCoor_1 = {200, 100};
    result_1 = calculateReducedCoor(cCoor_1, 400, 200);
    result_2 = calculatePolarCoor(result_1);
    cout << "Reduced cCoor_1: {" << result_1->x_Reduced << ", " << result_1->y_Reduced << "}" << endl;
    cout << "Transformed result_1: {" << result_2->r << ", " << result_2->phi << "}" << endl;
    cout << "Rad to deg: " << radToDeg(result_2->phi) << endl << endl;

    *cCoor_1 = {342, 80};
    result_1 = calculateReducedCoor(cCoor_1, 400, 200);
    result_2 = calculatePolarCoor(result_1);
    cout << "Reduced cCoor_1: {" << result_1->x_Reduced << ", " << result_1->y_Reduced << "}" << endl;
    cout << "Transformed result_1: {" << result_2->r << ", " << result_2->phi << "}" << endl;
    cout << "Rad to deg: " << radToDeg(result_2->phi) << endl << endl;

    *cCoor_1 = {10, 20};
    result_1 = calculateReducedCoor(cCoor_1, 400, 200);
    result_2 = calculatePolarCoor(result_1);
    cout << "Reduced cCoor_1: {" << result_1->x_Reduced << ", " << result_1->y_Reduced << "}" << endl;
    cout << "Transformed result_1: {" << result_2->r << ", " << result_2->phi << "}" << endl;
    cout << "Rad to deg: " << radToDeg(result_2->phi) << endl << endl;

    *cCoor_1 = {300, 180};
    result_1 = calculateReducedCoor(cCoor_1, 400, 200);
    result_2 = calculatePolarCoor(result_1);
    cout << "Reduced cCoor_1: {" << result_1->x_Reduced << ", " << result_1->y_Reduced << "}" << endl;
    cout << "Transformed result_1: {" << result_2->r << ", " << result_2->phi << "}" << endl;
    cout << "Rad to deg: " << radToDeg(result_2->phi) << endl << endl;

    return (0);
}
