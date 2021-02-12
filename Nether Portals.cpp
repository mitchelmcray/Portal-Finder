#include <iostream>
#include <tuple>
#include <set>
using namespace std;

//function declarations
set<tuple<int,int,int>> get_all_coords(tuple<int,int,int> coordinate, int distance);
tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> get_constraints(
    tuple<int, int, int> coordinates, int distance);
tuple<int, int> get_range(int coordinate, int distance);
int test_coordinate_set(set<tuple<int, int ,int>> coordinate_set, int distance, 
        tuple<int, int, int> base_coordinate);
int get_distance(tuple<int, int, int> x, tuple<int, int, int> y);


int main()
{
    /*tuple<int, int, int> test_coords = make_tuple(1,2,3);
    int distance = 5;
    set<tuple<int, int, int>> test;
    set<tuple<int, int, int>>::iterator test_iter;
    bool inserted;
    int elim;
    tie(test_iter, inserted) = test.insert(test_coords);
    elim = test.erase(test_coords);

    cout <<"Insertion: \r\n" << inserted << " " << elim << "\r\n";

    tie(test_iter, inserted) = test.insert(test_coords);
    elim = test.erase(make_tuple(3,2,1));

    cout <<"Insertion (false): \r\n" << inserted << " " << elim << "\r\n";
    
    
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

    set<tuple<int, int, int>> test_set = get_all_coords(test_coords, distance);*/

    set<tuple<int,int,int>> test_set_validation;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            for(int k=-1;k<2;k++){
                tuple<int,int,int> current_test_coord = make_tuple(i,j,k);
                test_set_validation.insert(current_test_coord);
            }
        }
    }
    set<tuple<int,int,int>>::iterator test_it = test_set_validation.begin();
    set<tuple<int,int,int>>::iterator test_end_it = test_set_validation.end();
    while(test_it != test_end_it){
        int test_x, test_y, test_z;
        tie(test_x, test_y, test_z) = *test_it;
        cout << "x: " << test_x << "y: " << test_y << "z: " << test_z <<"\r\n";
        test_it++;
    }
    bool tests = test_coordinate_set(test_set_validation, 1, make_tuple(0,0,0));
    return 0;
}

/**
 * Performs data validation on the given coordinate set.
 * 
 * test_coordinate_set makes sure that the given coordinate_set contains as many
 *     elements as would be expected for the given distance. It also makes sure that
 *     all coordinates in the set are within the given distance of base_coordinate.
 * 
 * @param coordinate_set - A set of tuples containing 3D coordinates
 * @param distance - An int representing the maximum allowed manhattan distance from
 *                   base_coordinate
 * @param base_coordinate - A tuple containing the 3D coordinate to use for referance
 * @return - 1 if all validity tests pass, and 0 if any fail
 */
int test_coordinate_set(set<tuple<int, int ,int>> coordinate_set, int distance, 
        tuple<int, int, int> base_coordinate){
    int set_size = coordinate_set.size();
    int expected_size = distance*distance*distance;
    bool size_test = (set_size==expected_size);
    if(!size_test){
        if(set_size<expected_size){
            cout << "ERROR: Set has fewer elements than expected";
        } else {
            cout << "ERROR: Set has more elements than expected";
        }
    }

    set<tuple<int, int, int>>::iterator coord_it = coordinate_set.begin();
    set<tuple<int, int, int>>::iterator end_it = coordinate_set.end();
    bool distance_test = true;
    while(coord_it != end_it){
        int calculated_distance = get_distance(*coord_it, base_coordinate);
        distance_test = distance_test && (calculated_distance <= distance);
        coord_it++;
    }
    return size_test && distance_test;
}
/**
 * Finds the Manhattan distance between two coordinates
 * 
 * @param x - A tuple of ints representing the first 3D coordinate
 * @param y - A tuple of ints representing the second 3D coordinate
 * @return - The result of |x1-y1| + |x2-y2| + |x3-y3|
 */
int get_distance(tuple<int, int, int> x, tuple<int, int, int> y){
    //Decompose coordinates
    int x1, x2, x3, y1, y2, y3;
    tie(x1, x2, x3) = x;
    tie(y1, y2, y3) = y;
    //Return distance
    return abs(x1-y1) + abs(x2-y2) + abs(x3-y3);
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