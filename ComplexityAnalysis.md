# Complexity Analysis

Let n be active reservations, q waiting-list entries, and h cancellations. Assume bounded-size records and comparisons; copying and printing variable-length strings also depend on their lengths.

| Operation | Time | Explanation |
| --- | --- | --- |
| Reservation insertion | O(1), or O(n) with validation | The current manager inserts at the linked-list head. A scan for duplicate IDs or resource/date conflicts makes the complete validated operation O(n). |
| Reservation removal | O(n) | Search by ID is linear; unlinking a located node is O(1). Retrieving a full record first adds a second linear scan but remains O(n). Saving it to the stack adds O(1). |
| Waiting-list enqueue | O(1) | The manager maintains a rear pointer. |
| Waiting-list removal | O(q) worst case | The current function searches by student and resource. Removing a matching front entry takes O(1). |
| Waiting-list display | O(q) plus output length | Traverses all queue nodes. Count and emptiness checks are O(1). |
| Undo cancellation | O(1) stack work plus restoration cost | Peek/pop are O(1). If the restoration callback scans n reservations for conflicts and inserts at the head, the full operation is O(n). Empty history returns in O(1). Additional resource or queue searches add their costs. |

Push, peek, pop, empty, and size are O(1). History display is O(h) plus output length. Clear and destruction take O(h), using iterative deletion and O(1) auxiliary space. Total stack storage is O(h). Blocked undo retains the top entry.

The current repository has no automatic promotion implementation. A front-pointer dequeue can be O(1), but validating/promoting waiting students adds its own costs. Processing q students with an O(n) validation scan per student would be O(qn).

Based on revision 8017b80a61dcb6d6663f0363c273f2f84433f430. Existing compilation errors need correction; list and queue bounds describe the visible algorithms. Recheck if those algorithms change.
