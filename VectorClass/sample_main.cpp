#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Stress_ball.h"
#include "Jeans.h"
#include "Collection.h"

using namespace std;

using CollectionSB = Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes>;
using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

#define LOG_LINE (cout << "Reached Line: " << __LINE__ << endl);

int main()
{
    srand(time(NULL));

    Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large);
    Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large);
    Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::medium);

    LOG_LINE;

    Jeans(Jeans_colors::white, Jeans_sizes::small);
    Jeans(Jeans_colors::black, Jeans_sizes::medium);
    Jeans(Jeans_colors::blue, Jeans_sizes::large);
    Jeans(Jeans_colors::grey, Jeans_sizes::xlarge);

    LOG_LINE;

    CollectionSB empty_sb;
    CollectionJN empty_jn;

    if(empty_sb.total_items() != 0 || empty_jn.total_items() != 0){
        cout << __LINE__ << " Error creating default collections." << endl;
        exit(1);
    }

    LOG_LINE;

    ifstream is_sb("stress_ball1.data");

    if(!is_sb){
        cout << __LINE__ << " Error opening data file" << endl;
        exit(1);
    }

    CollectionSB file_collection_sb;
    is_sb >> file_collection_sb;

    if(file_collection_sb.total_items() != 10){
        cout << __LINE__ << " Error in stress ball collection expected 10 items got " << file_collection_sb.total_items() << endl;
        exit(1); 
        file_collection_sb.print_items();
    }

    LOG_LINE;

    ifstream is_jn("jeans1.data");

    if(!is_jn){
        cout << __LINE__ << " Error opening data file" << endl;
        exit(1);
    }

    CollectionJN file_collection_jn;
    is_jn >> file_collection_jn;

    if(file_collection_jn.total_items() != 12){
        cout << __LINE__ << " Error in jean collection expected 12 items got " << file_collection_jn.total_items() << endl;

        exit(1); 
    }

    LOG_LINE;

    cout << "Tests passed, moving onto destructors.";

    return 0;
}
