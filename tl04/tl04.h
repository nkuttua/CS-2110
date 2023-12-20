/**
 * \mainpage Timed Lab 4: C and Dynamic Memory Allocation
 *
 * Office hours for CS 2110 are often very crowded. To manage this complexity,
 * the TAs have tasked you with building a queueing system. When a student
 * arrives at office hours, they are added to the end of the line. When a TA is
 * ready, they remove the person at the front of the line and service them.
 * Thus, the office hours queue is a first-come-first-served structure, or
 * alternatively a first-in-first-out structure.
 *
 * To implement this queue, you will use a singly-linked list. Each node in the
 * list contains data for a student, as well as a pointer to the next node in
 * the list (or `NULL` if it's the last node). The list will also have external
 * pointers to the `head` (frontmost) and `tail` (backmost) elements.
 *
 * Note that dynamic memory allocation is required here. It's unknown a priori
 * how many students will be in the queue at any given time. You have to be able
 * to allocate nodes on the fly.
 */

#ifndef TL04_H
#define TL04_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


/**
 * \brief Marks unused variables
 */
#define UNUSED(x) (void)(x)

/**
 * The return values for your functions
 * \property SUCCESS
 * \property FAILURE
 */
#define SUCCESS (0)
#define FAILURE (1)


/**
 * \brief All the assignments students can possibly need help on
 * \see student_t
 */
enum assignment_t {
    HOMEWORK_1, HOMEWORK_2, HOMEWORK_3, HOMEWORK_4, HOMEWORK_5,
    HOMEWORK_6, HOMEWORK_7, HOMEWORK_8, HOMEWORK_9, HOMEWORK_10,
    QUIZ_1, QUIZ_2, QUIZ_3, QUIZ_4,
    TIMED_LAB_1, TIMED_LAB_2, TIMED_LAB_3, TIMED_LAB_4,
};

/**
 * \brief Student to be stored in the queue
 *
 * This type represents individual students in the office hours queue. Each
 * student has a string for their name, as well as the assignment that they need
 * help on. For example, a student might be named `"George P. Burdell"` and need
 * help on `HOMEWORK_1`.
 */
struct student_t {
    char *name;              ///< Name of the student as a string
    enum assignment_t assignment; ///< Assignment the student needs help on
};


/**
 * \brief Node in the queue
 *
 * The office hours queue is represented by a singly-linked list. Each node in
 * the list has a [student_t] as data, but it also need a pointer to the next
 * node in the list. Hence, we wrap the [student_t] structure into a
 * [queue_node_t] with this auxilary data.
 */
struct queue_node_t {
    struct student_t data;     ///< The student held by this node
    struct queue_node_t *next; ///< Pointer to next node of list (or `NULL`)
};

/**
 * \brief Pointers to the ends of the list
 *
 * These pointers keep track of where the singly-linked list is in memory. The
 * [queue_head] pointer points to the first node of the list, and [queue_tail]
 * likewise points to the last.
 *
 * Initially, both of these pointers are `NULL`. The list is initially empty, so
 * there is no first or last node.
 *
 * \property extern queue_node_t *queue_head
 * \property extern queue_node_t *queue_tail
 */
extern struct queue_node_t *queue_head;
extern struct queue_node_t *queue_tail;


/**
 * \brief Add students to the queue
 *
 * This function will be called by client code to add a student to the end of
 * the queue. The caller will supply the data of the student to add.
 *
 * This function should wrap the [data] in a [queue_node_t] on the heap, and
 * deep-copy all the other data. In particular, the name of the student should
 * be moved onto the heap as well.
 *
 * This function should return `SUCCESS` if the student was added successfully.
 * If it fails, it should return `FAILURE` and leave the list unchanged. It
 * should fail if and only if:
 * * `malloc` fails,
 * * the student's name is `NULL`, or
 * * the student's name is an empty string.
 *
 * \param[in] data Data of the student to enqueue
 * \return Whether the student was successfully added
 */
extern int queue_add(struct student_t data);

/**
 * \brief Remove students from the queue
 *
 * This function will be called by client code to remove a student from the
 * front the queue. It will return whether a student was removed successfully,
 * and the data removed in that case.
 *
 * The way this function returns the data is somewhat strange. To get around the
 * limitation that functions may only have one return value, the caller will
 * pass in a pointer where the student's data should be stored. This function
 * will store the returned data at that pointer. Independently, it will return
 * whether it succeeded via the normal path.
 *
 * If this function succeeds, it should return `SUCCESS` and modify `*data` to
 * be the data of the student removed. If it fails, it should return `FAILURE`
 * and leave both the list and `*data` unchanged. It should fail if and only if:
 * * [data] is `NULL`, or
 * * the list is empty.
 *
 * Remember to free the node when you're done. Even though the data is being
 * returned, the node containing the data is not. The node will no longer be
 * accessible when the method returns, so it should be freed.
 *
 * \param[out] data Where to put the data of the removed student
 * \return Whether a student was successfully removed
 */
extern int queue_remove(struct student_t *data);


#endif // #ifndef TL04_H
