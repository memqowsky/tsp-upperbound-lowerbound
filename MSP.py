from math import floor
import matplotlib.pyplot as plt

def main():

    plt.figure(num='MSP')

    x_values = []
    y_values = []
    values = []

    f = open("res.txt", "r")
    
    for e in f:
        for n in e.split():
            values.append(n) # wczytujemy wszystkie liczby z pliku tekstowego do zmiennej

    for i in range(len(values)):
        if(i%2 == 0):
            x_values.append(values[i]) # parzyste zapisujemy do tablicy x
        else:
            y_values.append(values[i]) # nieparzyste zapisujemy do tablicy y

    f.close()

    # konwertujemy tablice str na tablice intow ---------------------------------------

    int_x_values = [int(numeric_string) for numeric_string in x_values]
    int_y_values = [int(numeric_string) for numeric_string in y_values]

    # wyznaczamy skrajne wartosci i zwiekszamy je o 20% w celu ustawienia okna. -------
    # W ten sposób cale drzewo rozpinajace bedzie wewnatrz okna -----------------------

    addon_x = int(max(int_x_values))
    addon_x = addon_x *0.2
    addon_y = int(max(int_y_values))
    addon_y = addon_y *0.2
 
    xmin = int(min(int_x_values))
    xmin -= addon_x

    xmax = int(max(int_x_values))
    xmax += addon_x

    ymin = int(min(int_y_values))
    ymin -= addon_y

    ymax = int(max(int_y_values))
    ymax += addon_y    

    # rysujemy punkty -----------------------------------------------------------------

    for _ in int_x_values:     

        plt.xlim(xmin,xmax)
        plt.ylim(ymin,ymax)
        plt.scatter(int_x_values, int_y_values, color='red', zorder=1)

    # dzielimy liste na podlisty -----------------------------------------------------

    split_lists_x = [int_x_values[x:x+2] for x in range(0, len(int_x_values), 2)]
    split_lists_y = [int_y_values[x:x+2] for x in range(0, len(int_y_values), 2)]

    # rysujemy krawedzie  ------------------------------------------------------------
    
    for i in range (len(split_lists_x)):
        plt.plot(split_lists_x[i],split_lists_y[i], zorder=0, color='black') 

    plt.savefig('msp.png') # zapisujemy do pliku png
    plt.show() # wyswietlamy na ekran

main()

