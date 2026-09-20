#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H
#include <cstddef>
#include <ostream>

// Record must own its data and be copyable.
template <typename Record>
class CancellationHistory {
    struct Node {
        Record reservation;
        Node* next;
        Node(const Record& value, Node* link) : reservation(value), next(link) {}
    };
    Node* top_ = nullptr;
    std::size_t size_ = 0;
public:
    enum class UndoResult { Restored, Empty, Blocked };
    CancellationHistory() = default;
    CancellationHistory(const CancellationHistory&) = delete;
    CancellationHistory& operator=(const CancellationHistory&) = delete;
    ~CancellationHistory() { clear(); }
    bool empty() const noexcept { return top_ == nullptr; }
    std::size_t size() const noexcept { return size_; }
    void push(const Record& reservation) {
        top_ = new Node(reservation, top_);
        ++size_;
    }
    const Record* peek() const noexcept {
        return top_ ? &top_->reservation : nullptr;
    }
    bool pop() noexcept {
        if (empty()) return false;
        Node* old = top_;
        top_ = old->next;
        delete old;
        --size_;
        return true;
    }
    void clear() noexcept { while (pop()) {} }

    // Callbacks must leave external state unchanged on false or exception,
    // and must not modify this history object.
    template <typename RemoveActive>
    bool cancel(const Record& reservation, RemoveActive removeActive) {
        push(reservation); // Copy before the active node can be deleted.
        try {
            if (removeActive(top_->reservation)) return true;
        } catch (...) {
            pop();
            throw;
        }
        pop();
        return false;
    }
    template <typename RestoreActive>
    UndoResult undo(RestoreActive restoreActive) {
        if (empty()) return UndoResult::Empty;
        if (!restoreActive(top_->reservation)) return UndoResult::Blocked;
        pop();
        return UndoResult::Restored;
    }
    template <typename Printer>
    void display(std::ostream& out, Printer print) const {
        if (empty()) { out << "No cancelled reservations.\n"; return; }
        for (const Node* node = top_; node; node = node->next) {
            print(out, node->reservation);
            out << '\n';
        }
    }
};
#endif
