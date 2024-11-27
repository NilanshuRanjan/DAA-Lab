#include <bits/stdc++.h>
using namespace std;
void SPI_cal(vector<int> &credit, vector<int> &grade, vector<int> &spi)
{
    cout << "Enter number of subjects:" << endl;
    int n, c, g;
    cin >> n;
    int total_credit = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter credit and grade for subject
                "<<i<<endl;
                cin >>
            c >> g;
        grades.push_back(g);
        credit.push_back(c);
        total_credit += c;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += grade[i] * credit[i];
    }
    float SPI = 1.0 * sum / tot ered;
    spi.push_back(SPI);
    cout << "Your spi is: " << SPI << endl;
}
float CPI_cal(vector<int> spi)
{
    int n = spi.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += spi[i];
    }
    // result
    float CPI = 1.0 * sum / n;
    cout << "Your cpi is: " << CPI << endI;
    return CPI;
}

int main()
{
    vector<int> grades;
    vector<int> credits;
    vector<int> spi;
    int n;
    cout << "enter number of semester: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        SPI_cal(grades, credits, spi);
    }
    CPI_cal(spi);
    return 0;
}