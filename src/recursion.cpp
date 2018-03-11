/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

Map<string, int> flag_arg;

int gcd(int a, int b){
    if (b == 0){
        cout << "gcd(" << a << "," << b << ") == 0" << endl;
        return a;
    }
    else{
        cout << "gcd(" << a << "," << b << ") == gcd(" << b << "," << a % b << ")" << endl;
        return gcd(b, a % b);
    }
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order){
    if (order < 0){
        throw "order can't be negative";
    }
    else if (order == 0){
        //draw nothing
    }
    else if (order == 1){
        w.drawLine(leftX, leftY, leftX + size, leftY);
        w.drawLine(leftX + size, leftY, leftX + size / 2, (sqrt(3) / 2) * size);
        w.drawLine(leftX + size / 2, (sqrt(3) / 2) * size, leftX, leftY);
    }
    else{
        w.drawLine(leftX + size / 4, leftY + (sqrt(3) / 4) * size, leftX + size * 3 / 4, leftY + (sqrt(3) / 4) * size);
        w.drawLine(leftX + size * 3 / 4, leftY + (sqrt(3) / 4) * size, leftX + size / 2, leftY);
        w.drawLine(leftX + size / 2, leftY, leftX + size / 4, leftY + (sqrt(3) / 4) * size);
        serpinskii(w, leftX, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 2, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 4, leftY + (sqrt(3) / 4) * size, size / 2, order - 1);
    }
}

int tool_floodFill(GBufferedImage &image, int x, int y, int newColor, int old){
    if (image.inBounds(x, y) && old == image.getRGB(x, y)){
        image.setRGB(x, y, newColor);
        return tool_floodFill(image, x + 1, y, newColor, old) + tool_floodFill(image, x - 1, y, newColor, old) + tool_floodFill(image, x, y - 1, newColor, old) + tool_floodFill(image, x, y + 1, newColor, old);
    }
    else{
        return 0;
    }
}

int floodFill(GBufferedImage &image, int x, int y, int newColor){
    int currentColor = image.getRGB(x, y);
    if (currentColor == newColor){
        return 0;
    }
    else{
        return tool_floodFill(image, x, y, newColor, currentColor);
    }
}

void tool_for_personalCurriculum(Map<string, Vector<string>> &prereqMap, string goal){
    if (prereqMap.get(goal).isEmpty() && !flag_arg.containsKey(goal)){
        cout << goal << endl;
        flag_arg.put(goal, 1);
    }
    else{
        for (auto concept : prereqMap.get(goal)){
            tool_for_personalCurriculum(prereqMap, concept);
            if (!flag_arg.containsKey(concept)){
                cout << concept << endl;
                flag_arg.put(concept, 1);
            }
        }
    }
}

void personalCurriculum(Map<string, Vector<string>> &prereqMap, string goal){
    tool_for_personalCurriculum(prereqMap, goal);
    cout << goal << endl;
}

// string getres(Map<string, Vector<string>> &grammer, string symbol, string out){
//     if (!grammer.containsKey(symbol)){
//         return symbol;
//     }
//     else{
//         string random = grammer.get(symbol).get(randomInteger(0, grammer.get(symbol).size() - 1));
//         TokenScanner scanner(random);
//         while (scanner.hasMoreTokens()){
//             string next = scanner.nextToken();
//             out += generate(grammer, next);
//         }
//     }
//     return out;
// }

// string generate(Map<string, Vector<string>> &grammer, string symbol){
//     return getres(grammer, symbol, "");
// }

string generate(Map<string, Vector<string>> &grammar, string symbol){
    string str;
    Vector<string> value;
    if (grammar.containsKey(symbol)){
        value = grammar.get(symbol);
        int randomNum = randomInteger(0, value.size() - 1);
        string randomStr = value.get(randomNum);
        TokenScanner tokenScanner(randomStr);
        while (tokenScanner.hasMoreTokens()){
            string newToken = tokenScanner.nextToken();
            str += generate(grammar, newToken);
        }
    }
    else{
        str += symbol;
    }
    return str;
}
