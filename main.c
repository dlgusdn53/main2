#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================
// 노드 및 리스트 구조체
// ============================================================
typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

typedef struct {
    ListNode* head;
    int size;
} LinkedList;

// ============================================================
// ADT 함수 구현
// ============================================================

// 공백 리스트 생성, Head를 NULL로 초기화
LinkedList* createLinkedList() {
    LinkedList* LS = (LinkedList*)malloc(sizeof(LinkedList));
    LS->head = NULL;
    LS->size = 0;
    return LS;
}

// 모든 노드의 메모리 해제 후 리스트 구조체 소멸
void destroyLinkedList(LinkedList* LS) {
    ListNode* cur = LS->head;
    while (cur != NULL) {
        ListNode* tmp = cur;
        cur = cur->link;
        free(tmp);
    }
    free(LS);
}

// 리스트가 비어있으면 true, 아니면 false
bool isEmptyLinkedList(LinkedList* LS) {
    return LS->head == NULL;
}

// 현재 노드의 총 개수 반환
int sizeLinkedList(LinkedList* LS) {
    return LS->size;
}

// 맨 앞에 삽입
void insertFirstLinkedList(LinkedList* LS, element item) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = item;
    newNode->link = LS->head;
    LS->head = newNode;
    LS->size++;
}

// 맨 뒤에 삽입
void insertLastLinkedList(LinkedList* LS, element item) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = item;
    newNode->link = NULL;
    if (isEmptyLinkedList(LS)) {
        LS->head = newNode;
    } else {
        ListNode* cur = LS->head;
        while (cur->link != NULL) cur = cur->link;
        cur->link = newNode;
    }
    LS->size++;
}

// 특정 노드(pre) 다음에 삽입
void insertItemLinkedList(LinkedList* LS, ListNode* pre, element item) {
    if (pre == NULL) {
        insertFirstLinkedList(LS, item);
        return;
    }
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = item;
    newNode->link = pre->link;
    pre->link = newNode;
    LS->size++;
}

// at번째 위치에 삽입 (0-based)
void insertAtLinkedList(LinkedList* LS, int at, element item) {
    if (at < 0 || at > LS->size) {
        printf("유효하지 않은 위치입니다.\n");
        return;
    }
    if (at == 0) {
        insertFirstLinkedList(LS, item);
        return;
    }
    ListNode* cur = LS->head;
    for (int i = 0; i < at - 1; i++) cur = cur->link;
    insertItemLinkedList(LS, cur, item);
}

// 첫 번째 노드 삭제 후 데이터 반환
element deleteFirstLinkedList(LinkedList* LS) {
    if (isEmptyLinkedList(LS)) {
        printf("리스트가 비어있습니다.\n");
        return -1;
    }
    ListNode* target = LS->head;
    element val = target->data;
    LS->head = target->link;
    free(target);
    LS->size--;
    return val;
}

// 마지막 노드 삭제 후 데이터 반환
element deleteLastLinkedList(LinkedList* LS) {
    if (isEmptyLinkedList(LS)) {
        printf("리스트가 비어있습니다.\n");
        return -1;
    }
    element val;
    if (LS->head->link == NULL) {
        val = LS->head->data;
        free(LS->head);
        LS->head = NULL;
    } else {
        ListNode* cur = LS->head;
        while (cur->link->link != NULL) cur = cur->link;
        val = cur->link->data;
        free(cur->link);
        cur->link = NULL;
    }
    LS->size--;
    return val;
}

// 특정 위치(pos) 노드 삭제 후 데이터 반환 (0-based)
element deleteItemLinkedList(LinkedList* LS, int pos) {
    if (pos < 0 || pos >= LS->size) {
        printf("유효하지 않은 위치입니다.\n");
        return -1;
    }
    if (pos == 0) return deleteFirstLinkedList(LS);
    ListNode* cur = LS->head;
    for (int i = 0; i < pos - 1; i++) cur = cur->link;
    ListNode* target = cur->link;
    element val = target->data;
    cur->link = target->link;
    free(target);
    LS->size--;
    return val;
}

// at번째 위치 노드 삭제 후 데이터 반환 (0-based)
element deleteAtLinkedList(LinkedList* LS, int at) {
    return deleteItemLinkedList(LS, at);
}

// 특정 위치(pos)의 데이터 반환 (0-based)
element getItemLinkedList(LinkedList* LS, int pos) {
    if (pos < 0 || pos >= LS->size) {
        printf("유효하지 않은 위치입니다.\n");
        return -1;
    }
    ListNode* cur = LS->head;
    for (int i = 0; i < pos; i++) cur = cur->link;
    return cur->data;
}

// 특정 위치(pos)의 데이터를 새로운 값으로 교체 (0-based)
void replaceItemLinkedList(LinkedList* LS, int pos, element item) {
    if (pos < 0 || pos >= LS->size) {
        printf("유효하지 않은 위치입니다.\n");
        return;
    }
    ListNode* cur = LS->head;
    for (int i = 0; i < pos; i++) cur = cur->link;
    cur->data = item;
}

// pre 위치의 다음 데이터 반환 (순차 탐색용)
element nextItemLinkedList(LinkedList* LS, ListNode* pre) {
    if (pre == NULL || pre->link == NULL) {
        printf("다음 노드가 없습니다.\n");
        return -1;
    }
    return pre->link->data;
}

// 모든 노드 데이터 순서대로 출력
void printLinkedList(LinkedList* LS) {
    if (isEmptyLinkedList(LS)) {
        printf("(빈 리스트)\n");
        return;
    }
    ListNode* cur = LS->head;
    printf("[ ");
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->link != NULL) printf(" -> ");
        cur = cur->link;
    }
    printf(" ]\n");
}

// ============================================================
// 메뉴
// ============================================================
void print_menu() {
    printf("\n====== 연결 리스트 메뉴 ======\n");
    printf(" 1. 맨 앞에 추가\n");
    printf(" 2. 맨 뒤에 추가\n");
    printf(" 3. 특정 위치에 추가 (index)\n");
    printf(" 4. 특정 위치 삭제 (index)\n");
    printf(" 5. 전체 목록 출력\n");
    printf(" 6. 리스트 크기 확인\n");
    printf(" 0. 종료\n");
    printf("==============================\n");
    printf("선택: ");
}

// ============================================================
// main
// ============================================================
int main() {
    LinkedList* LS = createLinkedList();
    int choice, at, item;

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 정수: ");
                scanf("%d", &item);
                insertFirstLinkedList(LS, item);
                printf("%d을(를) 맨 앞에 추가했습니다.\n", item);
                break;

            case 2:
                printf("삽입할 정수: ");
                scanf("%d", &item);
                insertLastLinkedList(LS, item);
                printf("%d을(를) 맨 뒤에 추가했습니다.\n", item);
                break;

            case 3:
                printf("삽입할 위치(0-based index): ");
                scanf("%d", &at);
                printf("삽입할 정수: ");
                scanf("%d", &item);
                insertAtLinkedList(LS, at, item);
                printf("%d을(를) %d번 위치에 추가했습니다.\n", item, at);
                break;

            case 4:
                printf("삭제할 위치(0-based index): ");
                scanf("%d", &at);
                item = deleteAtLinkedList(LS, at);
                if (item != -1)
                    printf("%d번 위치의 값 %d을(를) 삭제했습니다.\n", at, item);
                break;

            case 5:
                printf("현재 리스트: ");
                printLinkedList(LS);
                break;

            case 6:
                printf("리스트 크기: %d\n", sizeLinkedList(LS));
                break;

            case 0:
                destroyLinkedList(LS);
                printf("메모리를 해제하고 종료합니다.\n");
                return 0;

            default:
                printf("올바른 메뉴를 선택하세요.\n");
                break;
        }
    }
}
