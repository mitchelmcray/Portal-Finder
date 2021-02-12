#include <iostream>
#include <tuple>
#include <set>
using namespace std;

//function declarations
set<tuple<int,int,int>> get_all_coords(tuple<int,int,int> coordinate, int distance);
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

    set<tuple<int, int, int>> test_set = get_all_coords(test_coords, distance);

    return 0;
}

/**
 * 
 *
int test_coordinate_set(set<tuple<int, int ,int>> coordinate_set, int distance){
    int set_size = coordinate_set.size();
    int expected_size = distance*distance*distance;
    if(!(set_size==expected_size)){
        if(set_size<expected_size){
            cout << "ERROR: Set has fewer elements than expected";
        } else {
            cout << "ERROR: Set has more elements than expected";
        }
    }

    set<tuple<int, int, int>>::iterator coord_it = coordinate_set.begin();
    set<tuple<int, int, int>>::iterator end_it = coordinate_set.end();
    while(coord_it != end_it){
        check_distance(*it);
    }
}*/


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
    //Declare return value and initial control variables
    set<tuple<int, int, int>> to_return;
    int x, y, z, y_lower, y_upper;
    //Decompose coordinate into int values
    tie(x, y, z) = coordinate;
    //Get the lower and upper bounds of y-coordinate for given distance
    tie(y_lower, y_upper) = get_range(y, distance); //y_upper is currently unused
    
    //Iterate over each integer value between y_lower and y_upper (y_upper = y_lower + 2*distance)
    for(int i=0; i<=(2*distance);i++){
        //Calculate actual y-coordinate value for the current iteration
        int current_y = y_lower +i;
        //Calculate the current upper bound on the absoulte value for the x-coordinate
        int j_bound = distance-abs(distance-i);

        //Iterate over the absolute values for the distances of the current possible x-coordinates
        for(int j=0; j<=j_bound;j++){
            //Declare and initialize control variables related to the x-coordinate
            int min_x, plus_x, k_bound = j_bound-j; //determine the bound on the z-coordinate from the x
            //Calculate the actual x-coordinate values from the current distance
            min_x = x-j;
            plus_x = x+j;

            //Iterate over the absolute values for the distances of the current possible z-coordinates
            for(int k=0; k<=k_bound;k++){
                //Declare and initialize control variables related to the z-coordinate
                int min_z, plus_z;
                min_z = z-k;
                plus_z = z+k;

                //Insert all possible coordinates for the current constraints
                if(!j){ //Check if current x-coordinate distance is 0
                    if(!k){ //Check if current z-coordinate distance is 0
                        to_return.insert(make_tuple(x, current_y, z));
                    } else {
                        to_return.insert(make_tuple(x, current_y, min_z));
                        to_return.insert(make_tuple(x, current_y, plus_z));
                    }
                } else { //Check if current z-coordinate distance is 0
                     if(!k){
                        to_return.insert(make_tuple(min_x, y, z));
                        to_return.insert(make_tuple(plus_x, y, z));
                    } else{
                        to_return.insert(make_tuple(min_x, y, min_z));
                        to_return.insert(make_tuple(min_x, y, plus_z));
                        to_return.insert(make_tuple(plus_x, y, min_z));
                        to_return.insert(make_tuple(plus_x, y, plus_z));
                    }
                }
            }
        }
    }
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