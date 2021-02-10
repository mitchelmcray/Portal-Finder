#include <iostream>
#include <tuple>
using namespace std;

//function declarations
tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> get_constraints(
    tuple<int, int, int> coordinates, int distance);
tuple<int, int> get_range(int coordinate, int distance);


int main()
{
    tuple<int, int, int> test_coords = make_tuple(1,2,3);
    int distance = 5;
    
    tuple<int, int> x_bounds, y_bounds, z_bounds;
    tie(x_bounds, y_bounds, z_bounds) = get_constraints(test_coords, distance);
    
    int x_left_bound, x_right_bound;
    tie(x_left_bound, x_right_bound) = x_bounds;
    cout<<"x bounds:\r\n" << x_left_bound << " " << x_right_bound << "\r\n";
    
    int y_left_bound, y_right_bound;
    tie(y_left_bound, y_right_bound) = y_bounds;
    cout<<"y bounds:\r\n" << y_left_bound << " " << y_right_bound << "\r\n";
    
    int z_left_bound, z_right_bound;
    tie(z_left_bound, z_right_bound) = z_bounds;
    cout<<"z bounds:\r\n" << z_left_bound << " " << z_right_bound << "\r\n";

    return 0;
}

/**
 * Finds the constraints for the given functions.
 * 
 * Returns the upper and lower bounds for each coordinate the would comprise
 *     solutions for the following equation: 
 *     |x-coordinate<x>| + |y-coordinate<y>| + |z-coordinate<z>| = distance
 * 
 * @param coordinates - a tumple containing a three dimensional coordinates
 * @param distance - an int containing a distance constraints
 * @return a triple of int duples containing the bounds for each coordinate
 */
tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> get_constraints(
    tuple<int, int, int> coordinates, int distance){
    //unpack coordinates
    int x, y, z;
    tie(x, y, z) = coordinates;
    //declare return variables
    tuple<int, int> x_bounds, y_bounds, z_bounds;
    
    //find bounds for each coordinate
    x_bounds = get_range(x, distance);
    y_bounds = get_range(y, distance);
    z_bounds = get_range(z, distance);
    
    //create return tuple and return
    tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> to_return = 
        make_tuple(x_bounds, y_bounds, z_bounds);
    return to_return;
    
}

/**
 * get_range returns the range bounds that would solve the equation 
 *    |x-coordinate| = distance for x.
 * 
 * @param coordinate - an int containing the current coordinate of interest
 * @param distance - an int containing the current distance constraint
 * @return a tuple of type <int, int> containing the result of solving the above
 *    equation for x. With the first index containing the result of solving for
 *    a negative distane, and the second a positive distance.
 */
tuple<int, int> get_range(int coordinate, int distance){
    tuple<int, int> output = make_tuple(-distance+coordinate, distance+coordinate);
    return output;
}