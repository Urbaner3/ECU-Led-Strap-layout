void TForm1::Check80x80PointLocation(int ang, int &x1, int &y1, int &x2, int &y2) {
    int point[4];
    int point2[4];
    int temp[2];
    unsigned int ang_flag = 0;

    if (x1 > x2 || y1 > y2) {                 // tree A if branch
        // Swap points
        point[0] = x2;
        point[1] = y2;
        point[2] = x1;
        point[3] = y1;
        ang_flag = 1;
    }
    else if (x2 > x1 || y2 > y1) {          //tree A else-if branch
        // No need to swap
        point[0] = x1;
        point[1] = y1;
        point[2] = x2;
        point[3] = y2;
    }
    else {                                   //tree A else-else branch
        // Points are the same, do nothing
        return;
    }

    if (point[0] != 0) {                    //tree B  if branch
        point2[2] = point[2] - point[0];
        temp[0] = 78 - point2[2];
    }
    else {
        temp[0] = 78 - point[2];
    }

    if (point[1] != 0) {
        point2[3] = point[3] - point[1];
        temp[1] = 78 - point2[3];
    }
    else {
        temp[1] = 78 - point[3];
    }

    x1 += temp[0];
    y1 += temp[1];
    x2 += temp[0];
    y2 += temp[1];
}
