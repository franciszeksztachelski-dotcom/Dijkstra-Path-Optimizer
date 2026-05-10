#include <iostream>


const int INFINITY_VAL = 1000000000;

struct Point {
    int x, y, distance;
};

struct Lift {
    int start_X, start_Y;
    int end_X, end_Y;
    int time, interval;
};

class PriorityQueue {
    Point* heap;
    int size = 0;
    
    void siftDown(int index) {
        while(true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if(left < size && heap[left].distance < heap[smallest].distance) smallest = left;
            if(right < size && heap[right].distance < heap[smallest].distance) smallest = right;
            if(smallest == index) break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

    void siftUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[parent].distance <= heap[index].distance) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void swap(Point& a, Point& b) {
    Point temp = a;
    a = b;
    b = temp;
} 

public:
    PriorityQueue(int maxSize) { heap = new Point[maxSize]; }
    ~PriorityQueue() { delete[] heap; }

    void push(const Point p) {
        heap[size] = p;
        siftUp(size++);
    }

    Point pop() {
        Point result = heap[0];
        heap[0] = heap[--size];
        if(size > 0) siftDown(0);
        return result;
    }

    bool empty() { return size == 0; }
};

int main() {
    
    int width, height, start_X, start_Y, end_X, end_Y;
    std::cin >> width >> height >> start_X >> start_Y >> end_X >> end_Y;
    
    int liftsCount;
    std::cin >> liftsCount;
    
    Lift* lifts = new Lift[liftsCount];
    for(int i = 0; i < liftsCount; i++) {
        std::cin >> lifts[i].start_X >> lifts[i].start_Y;
        std::cin >> lifts[i].end_X >> lifts[i].end_Y;
        std::cin >> lifts[i].time >> lifts[i].interval;
    }

    int** map = new int*[height];
    int** distance = new int*[height];
    bool** visited = new bool*[height];
    
    for(int i = 0; i < height; i++) {
        map[i] = new int[width];
        distance[i] = new int[width];
        visited[i] = new bool[width];
        for(int j = 0; j < width; j++) {
            std::cin >> map[i][j];
            distance[i][j] = INFINITY_VAL;
            visited[i][j] = false;
        }
    }

    distance[start_Y][start_X] = 0;
    PriorityQueue queue(width * height * 4);
    queue.push({start_X, start_Y, 0});

    const int dirX[] = {-1, 1, 0, 0};
    const int dirY[] = {0, 0, -1, 1};

    while(!queue.empty()) {
        Point current = queue.pop();
        if(visited[current.y][current.x]) continue;
        visited[current.y][current.x] = true;

        for(int i = 0; i < 4; i++) {
            int nextX = current.x + dirX[i];
            int nextY = current.y + dirY[i];
            
            if(nextX >= 0 && nextX < width && nextY >= 0 && nextY < height && !visited[nextY][nextX]) {
                int time = 1;
                if(map[nextY][nextX] > map[current.y][current.x]) 
                    time += map[nextY][nextX] - map[current.y][current.x];
                
                if(distance[current.y][current.x] + time < distance[nextY][nextX]) {
                    distance[nextY][nextX] = distance[current.y][current.x] + time;
                    queue.push({nextX, nextY, distance[nextY][nextX]});
                }
            }
        }

        for(int i = 0; i < liftsCount; i++) {
            if(current.x == lifts[i].start_X && current.y == lifts[i].start_Y) {
                int waitTime = lifts[i].interval > 0 ? 
                    (lifts[i].interval - (distance[current.y][current.x] % lifts[i].interval)) % lifts[i].interval : 0;
                
                int newTime = distance[current.y][current.x] + waitTime + lifts[i].time;
                if(newTime < distance[lifts[i].end_Y][lifts[i].end_X]) {
                    distance[lifts[i].end_Y][lifts[i].end_X] = newTime;
                    queue.push({lifts[i].end_X, lifts[i].end_Y, newTime});
                }
            }
        }
    }

    std::cout << distance[end_Y][end_X] << '\n';

    delete[] lifts;
    for(int i = 0; i < height; i++) {
        delete[] map[i];
        delete[] distance[i];
        delete[] visited[i];
    }
    delete[] map;
    delete[] distance;
    delete[] visited;

    return 0;
}