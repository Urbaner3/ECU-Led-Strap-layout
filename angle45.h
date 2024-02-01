
int TForm1::Angle_45(int angle, int length, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int point_buff[][100]) {
    double x, y;
    int ansabs;
    //note the dimension point_buff[2][100];
    // Calculate the average spread distance
    if (x1 == x2) {
        x = 0;
    }
    else if (x1 > x2) {
        ansabs = x1 - x2;
        x =
         abs(ansabs) / (length - 1);
    }
    else {
        ansabs = x2-x1;
        x = abs(ansabs) / (length - 1);
    }

    if (y1 == y2) {
        y = 0;
    }
    else if (y1 > y2) {
    ansabs = y1-y2;
        y = abs(ansabs) / (length - 1);
    }
    else {
    ansabs = y2-y1;
        y = abs(ansabs) / (length - 1);
    }

    // Plan and record coordinates
    for (int i = 0; i < length; ++i) {
        if (angle == 0 || angle == 360) {
            point_buff[0][i] = round(x2 + (i * x)); // X coordinate
            point_buff[1][i] = y2;                   // Y coordinate
        }
        else if (angle > 0 && angle < 90) {
            point_buff[0][i] = round(x2 + (i * x)); // X coordinate
            point_buff[1][i] = round(y2 - (i * y)); // Y coordinate
        }
        else if (angle == 90) {
            point_buff[0][i] = x2;                   // X coordinate
            point_buff[1][i] = round(y2 - (i * y)); // Y coordinate
        }
        else if (angle > 90 && angle < 180) {
            point_buff[0][i] = round(x2 - (i * x)); // X coordinate
            point_buff[1][i] = round(y2 - (i * y)); // Y coordinate
        }
        else if (angle == 180) {
            point_buff[0][i] = round(x2 - (i * x)); // X coordinate
            point_buff[1][i] = y2;                   // Y coordinate
        }
        else if (angle > 180 && angle < 270) {
            point_buff[0][i] = round(x2 - (i * x)); // X coordinate
            point_buff[1][i] = round(y2 + (i * y)); // Y coordinate
        }
        else if (angle == 270) {
            point_buff[0][i] = x2;                   // X coordinate
            point_buff[1][i] = round(y2 + (i * y)); // Y coordinate
        }
        else if (angle > 270 && angle < 360) {
            point_buff[0][i] = round(x2 + (i * x)); // X coordinate
            point_buff[1][i] = round(y2 + (i * y)); // Y coordinate
        }
        else if (angle == -360) {
            point_buff[0][i] = round(x1 + (i * x)); // X coordinate
            point_buff[1][i] = y1;                   // Y coordinate
        }
        else if (angle > -360 && angle < -270) {
            point_buff[0][i] = round(x1 + (i * x)); // X coordinate
            point_buff[1][i] = round(y1 - (i * y)); // Y coordinate
        }
        else if (angle == -270) {
            point_buff[0][i] = x1;                   // X coordinate
            point_buff[1][i] = round(y1 - (i * y)); // Y coordinate
        }
        else if (angle > -270 && angle < -180) {
            point_buff[0][i] = round(x1 - (i * x)); // X coordinate
            point_buff[1][i] = round(y1 - (i * y)); // Y coordinate
        }
        else if (angle == -180) {
            point_buff[0][i] = round(x1 - (i * x)); // X coordinate
            point_buff[1][i] = y1;                   // Y coordinate
        }
        else if (angle > -180 && angle < -90) {
            point_buff[0][i] = round(x1 - (i * x)); // X coordinate
            point_buff[1][i] = round(y1 + (i * y)); // Y coordinate
        }
        else if (angle == -90) {
            point_buff[0][i] = x1;                   // X coordinate
            point_buff[1][i] = round(y1 + (i * y)); // Y coordinate
        }
        else if (angle > -90 && angle < 0) {
			point_buff[0][i] = round(x1 + (i * x)); // X coordinate
            point_buff[1][i] = round(y1 + (i * y)); // Y coordinate
        }
        else {
            return 1;
        }
    }

    return 0;
}
