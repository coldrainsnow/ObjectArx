ads_point pt;
int res = acedGetPoint(NULL, _T("\nSelect a point:"), pt);
if (res == RTNORM) {
    // pt[0], pt[1], pt[2] contain the x, y, z coordinates of the selected point
    TCHAR str[256];
    _stprintf_s(str, _T("(%f,%f,%f)"), pt[0], pt[1], pt[2]);
    // str now contains the string representation of the point
}