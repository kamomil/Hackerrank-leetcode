#include <list>

class MinStack {

private:
    std::list<int,int> *_s;
    int _min_idx;
    int _min;

public:
    MinStack() {
        _s = new std::list<int,int>();
        min_idx = -1;
        min = 0;
    }

    void push(int val) {
        /* case where val is the new min */
        if (_min_idx == -1 || val <= _min) {
            _s->push(val, min_idx);
            _min = val;
            _min_idx = _s->size() - 1;
        } else {
            _s->push(val, -1);
        }
    }

    void pop() {
        if (_s->first()[0] == _min) {
            _min_idx = _s->first()[1];
            _min = _min_idx > -1 ? _s->at(_min_idx) : 0;
        }
        _s->pop();

    }

    int top() {
        return _s->first()[0];
    }

    int getMin() {
        return _s->min;
    }
};

int main ()
{
/**
 * Your MinStack object will be instantiated and called as such:
 **/

    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    obj->getMin();
    obj->pop();
    int param_2 = obj->top();
    obj->getMin();
    return 0;
}
