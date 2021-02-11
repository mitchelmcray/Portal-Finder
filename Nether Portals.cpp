#include <iostream>
#include <tuple>
#include <set>
using namespace std;

//function declarations
tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> get_constraints(
    tuple<int, int, int> coordinates, int distance);
tuple<int, int> get_range(int coordinate, int distance);


int main()
{
    tuple<int, int, int> test_coords = make_tuple(1,2,3);
    int distance = 5;
    /*set<tuple<int, int, int>> test;
    set<tuple<int, int, int>>::iterator test_iter;
    bool inserted;
    int elim;
    tie(test_iter, inserted) = test.insert(test_coords);
    elim = test.erase(test_coords);

    cout <<"Insertion: \r\n" << inserted << " " << elim << "\r\n";

    tie(test_iter, inserted) = test.insert(test_coords);
    elim = test.erase(make_tuple(3,2,1));

    cout <<"Insertion (false): \r\n" << inserted << " " << elim << "\r\n";*/
    
    
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
 * Finds all coordinates within a given distance.
 * 
 * Creates a set of all the three-dimensioal coordinates within the given 
 *     manhattan distance of the give coordinate.
 *  
 * @param coordinate - A tuple containing a 3D coordinate
 * @param distance - An int denoting the manhattan distance constrait
 * @return A set of tuples containing all the 3D coordinates
 */
set<tuple<int,int,int>> get_all_coords(tuple<int,int,int> coordinate, int distance){
    set<tuple<int, int, int>> to_return;
    return to_return;
}

/**
 * Finds the constraints for the given coordinates.
 * 
 * Returns the upper and lower bounds for each coordinate the would comprise
 *     solutions for the following equation: 
 *     |x-coordinate<x>| + |y-coordinate<y>| + |z-coordinate<z>| = distance
 * 
 * @param coordinates - a tuple containing a three dimensional coordinates
 * @param distance - an int containing the distance constraint
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
 * Finds the upper and lower bounds for the coordinate.
 * 
 * get_range returns the range bounds that would solve the equation 
 *    |x-coordinate| = distance for x.
 * 
 * @param coordinate - an int containing the current coordinate of interest
 * @param distance - an int containing the current distance constraint
 * @return a tuple of type <int, int> containing the result of solving the above
 *    equation for x. With the first index containing the lower bound, and the
 *    second the upper.
 */
tuple<int, int> get_range(int coordinate, int distance){
    //find initial bounds
    int leftBound = -distance+coordinate;
    int rightBound = distance+coordinate;
    tuple<int, int> to_return;

    //check which bound is lower, and create the tuple accordingly
    if(leftBound<rightBound){
        to_return = make_tuple(leftBound, rightBound);
    } else{
        to_return = make_tuple(rightBound, leftBound);
    }

    return to_return;
}