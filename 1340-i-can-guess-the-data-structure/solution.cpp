#include <bits/stdc++.h>

int main() {
    std::vector<std::string> answers;

    int operations;
    while (std::cin >> operations) {
        std::stack<int> stack;
        std::queue<int> queue;
        std::priority_queue<int> pqueue;

        std::vector<int> possibilities(3, 1); // [0] stack; [1] queue; [2] pqueue

        while (operations--) {
            int operation, element;
            std::cin >> operation >> element;

            if (operation == 1) {
                stack.push(element);
                queue.push(element);
                pqueue.push(element);
            }
            else {
                int selement = stack.top();
                int qelement = queue.front();
                int pqelement = pqueue.top();

                stack.pop();
                queue.pop();
                pqueue.pop();

                if (possibilities[0]) possibilities[0] = (selement == element);
                if (possibilities[1]) possibilities[1] = (qelement == element);
                if (possibilities[2]) possibilities[2] = (pqelement == element);
            }
        }

        int total_possibilities = std::accumulate(possibilities.begin(), possibilities.end(), 0);

        if (total_possibilities == 0) answers.push_back("impossible");
        else if (total_possibilities > 1) answers.push_back("not sure");
        else if (possibilities[0]) answers.push_back("stack");
        else if (possibilities[1]) answers.push_back("queue");
        else if (possibilities[2]) answers.push_back("priority queue");
    }

    for (const std::string& answer : answers) {
        std::cout << answer << std::endl;
    }

    return 0;
}
