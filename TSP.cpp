#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

struct vert
{
    int x, y;
};

struct edge
{
    int a, b;
    vert first, second;
    float len;
    bool chosen;
};

void InsertSort(edge t[], int r)
{
    for (int i = 1; i < r; i++)
    {
        int idx = i - 1;
        edge temp = t[i];
        while (idx >= 0 && t[idx].len > temp.len)
        {
            t[idx + 1] = t[idx];
            idx--;
        }
        t[idx + 1] = temp;
    }
}

float dist(vert A, vert B)
{
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

edge *Kruskal(vert V[], int how_many)
{
    int *color = new int[how_many];
    for (int i = 0; i < how_many; i++)
        color[i] = i;

    int n = 0;

    int num_of_edges = how_many * (how_many - 1) * 0.5;

    edge *E = new edge[num_of_edges];

    for (int i = 0; i < how_many; i++)
        for (int j = i + 1; j < how_many; j++)
        {
            E[n].a = i;
            E[n].b = j;
            E[n].len = dist(V[i], V[j]);
            E[n].chosen = false;
            E[n].first = V[i];
            E[n].second = V[j];
            n++;
        }

    InsertSort(E, num_of_edges);

    int counter = 0;

    for (int i = 0; i < num_of_edges; i++)
    {
        int c1 = color[E[i].a];
        int c2 = color[E[i].b];

        if (c1 != c2)
        {
            E[i].chosen = true;

            for (int j = 0; j < how_many; j++)
                if (color[j] == c2)
                    color[j] = c1;

            counter++;

            if (counter == how_many - 1)
                break;
        }
    }

    return E;
}

double upper(edge *e, int num_of_edges)
{
    double res = 0;

    for (int i = 0; i < num_of_edges; i++)
    {
        if (e[i].chosen)
        {
            res += e[i].len;
        }
    }

    return res * 2;
}

void write_to_file(edge *e, int num_of_edges)
{
    ofstream write("res.txt");

    for (int i = 0; i < num_of_edges; i++)
    {
        if (e[i].chosen)
        {
            write << e[i].first.x << " " << e[i].first.y << " " << e[i].second.x << " " << e[i].second.y << " ";
        }
    }

    write.close();
}

double lower(vert *v, int how_many)
{

    vector<double> d;
    vert *temp = new vert[how_many - 1];
    edge *res;
    int num_of_edges = (how_many - 1) * (how_many - 2) * 0.5;
    vector<double> bounds;
    double bound;

    for (int i = 0; i < how_many; ++i)
    {

        d.clear();

        for (int j = 0; j < how_many; j++)
        {
            d.push_back(dist(v[i], v[j]));
        }

        d.erase(remove(d.begin(), d.end(), 0), d.end());
        sort(d.begin(), d.end());

        temp = new vert[how_many - 1];

        vector<vert> vert_vector;

        for (int j = 0; j < how_many; j++)
        {
            if (j != i)
            {
                vert tv;
                tv.x = v[j].x;
                tv.y = v[j].y;
                vert_vector.push_back(tv);
            }
        }

        for (int j = 0; j < vert_vector.size(); j++)
        {
            temp[j].x = vert_vector[j].x;
            temp[j].y = vert_vector[j].y;
        }

        res = Kruskal(temp, how_many - 1);

        bound = 0;

        for (int j = 0; j < num_of_edges; j++)
        {
            if (res[j].chosen)
            {
                bound += res[j].len;
            }
        }

        bound += d[0];
        bound += d[1];

        bounds.push_back(bound);
    }

    delete[] temp;
    delete[] res;

    sort(bounds.begin(), bounds.end(), greater<double>());
    return bounds[0];
}

int main()
{

    ifstream ifstr("data.txt");

    int how_many = 0;
    int num_of_edges = 0;
    vert *V;
    vector<int> numbers;

    if (ifstr.is_open())
    {
        string word;
        ifstr >> how_many;
        V = new vert[how_many];

        num_of_edges = how_many * (how_many - 1) * 0.5;

        while (ifstr >> word)
        {
            for (int i = 0; i < word.length(); ++i)
            {
                if (word[i] == ',')
                {
                    word.erase(i);
                }
            }
            numbers.push_back(stoi(word));
        }
    }
    else
    {
        cout << "Cant open the file";
    }

    int k = 0;
    for (int i = 0; i < how_many; i++)
    {
        V[i].x = numbers[k];
        k++;
        V[i].y = numbers[k];
        k++;
    }

    edge *res;
    res = Kruskal(V, how_many);

    cout << endl;

    cout << "Upper bound: " << upper(res, num_of_edges) << endl;
    cout << "Lower bound: " << lower(V, how_many) << endl;
    write_to_file(res, num_of_edges);

    ifstr.close();
    delete[] V;
    delete[] res;

    return 0;
}