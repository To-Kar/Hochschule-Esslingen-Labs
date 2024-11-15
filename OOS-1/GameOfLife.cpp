#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define x_ 20
#define y_ 20

int main(int argc, char *argv[])
{

    char field[x_][y_];
    char newfield[x_][y_];
    int generation, livingCell;
    int x_pos, y_pos;
    char input;

    // anzahl an generation

    scanf("%d", &generation);

    // Spielfeld auffüllen mit punkten

    for (int i = 0; i < y_; i++)
    {

        for (int j = 0; j < x_; j++)
        {

            field[j][i] = '.';
        }
    }

    // an den positionen # für lebende Zelle einsetzen

    do
    {

        scanf("%c", &input);

        if (input == 'a')
        {

            scanf("%d %d", &x_pos, &y_pos);

            field[x_pos][y_pos] = '#';
        }

    } while (input != 'e');

    printf("-- Generation: 0\n");

    for (int y = 0; y < y_; y++)
    {
        for (int x = 0; x < x_; x++)
        {
            printf("%c", field[x][y]);
        }
        printf("\n");
    }

    // für die zwischenschritte damit das richtige field nicht überschrieben wird
    for (int i = 0; i < y_; i++)
    {
        for (int j = 0; j < x_; j++)
        {
            newfield[j][i] = field[j][i];
        }
    }

    for (int e = 1; e <= generation; e++)
    {
        printf("-- Generation: %d\n", e);

        for (int y = 0; y < y_; y++)
        {
            for (int x = 0; x < x_; x++)
            {

                if (field[x][y] == '.')
                {
                    livingCell = 0;
                    for (int i = y - 1; i < y + 2; i++) // Anzahl lebender zellen überprüfen
                    {
                        for (int j = x - 1; j < x + 2; j++)
                        {
                            if (field[j][i] == '#')
                            {
                                livingCell++;
                            }
                        }
                    }
                    if (livingCell == 3) // Regel 1: Tote Zelle Wiederbeleben
                    {
                        newfield[x][y] = '#';
                    }
                    printf("%c", newfield[x][y]);
                }
                // prüfen ob die zelle lebt
                else if (field[x][y] == '#')
                {
                    livingCell = 0;
                    for (int i = y - 1; i < y + 2; i++)
                    {
                        for (int j = x - 1; j < x + 2; j++)
                        {
                            if (field[j][i] == '#')
                            {
                                livingCell++;
                            }
                        }
                    }
                    livingCell = livingCell - 1;          // zählt sich selbst mit in der jetzigen generation soll abe rnicht mitgezählt werden in der folgendenen generation
                    if (livingCell < 2 || livingCell > 3) // Regel 2 und 3 2: lebende Zelle mit weniger als 2 nachbarn stirbt 3: lebende zelle mit zu vielen nachbarn stirbt
                    {
                        newfield[x][y] = '.';
                    }

                    printf("%c", newfield[x][y]);
                }
            }
            printf("\n");
        }
        for (int i = 0; i < y_; i++)
        {
            for (int j = 0; j < x_; j++)
            {
                field[j][i] = newfield[j][i];
            }
        }
    }

    return 0;
}