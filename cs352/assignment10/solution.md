Homework 10
===========

By Josh Davis

Due: Thurs, April 18 at midnight

## Problem 1

Frames = 256
Service page fault = 4ms
Replace page = 10ms
Mem access time = 100 nanoseconds
Percantage = 75%

What is the maximum acceptable page-fault rate in orer to achieve an effective
access time of no more than 200 nanoseconds?

    .0002ms = (1 - p) * (.0001ms) + p * ((10ms)*.75 + (1 - .75)(4ms))
            = 0.0000117648442922858

## Problem 2

Total number of page faults = 12

### Step 1

Step through below:

Page replacement reference string:
    1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 1

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     |         |      |
| 2     |         |      |
| 3     |         |      |
| 4     |         |      |

### Step 2

Page replacement reference string:
    2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 2

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     |         |      |
| 3     |         |      |
| 4     |         |      |

### Step 3

Page replacement reference string:
    3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 3

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     | 3       | 3    |
| 3     |         |      |
| 4     |         |      |

### Step 4

Page replacement reference string:
    4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 4

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     | 3       | 3    |
| 3     | 4       | 4    |
| 4     |         |      |

### Step 5

Page replacement reference string:
    5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 5

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     | 3       | 3    |
| 3     | 4       | 4    |
| 4     | 5       | 5    |

### Step 6

Page replacement reference string:
    3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 5

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     | 3       | 6    |
| 3     | 4       | 4    |
| 4     | 5       | 5    |

### Step 7

Page replacement reference string:
    4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 5

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 1    |
| 1     | 2       | 2    |
| 2     | 3       | 6    |
| 3     | 4       | 7    |
| 4     | 5       | 5    |

### Step 8

Page replacement reference string:
    1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 5

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 2       | 2    |
| 2     | 3       | 6    |
| 3     | 4       | 7    |
| 4     | 5       | 5    |

### Step 9

Page replacement reference string:
    6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 6

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 3       | 6    |
| 3     | 4       | 7    |
| 4     | 5       | 5    |

### Step 10

Page replacement reference string:
    7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 7

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 3       | 6    |
| 3     | 4       | 7    |
| 4     | 7       | 10   |

### Step 11

Page replacement reference string:
    8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 8

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 11   |
| 3     | 4       | 7    |
| 4     | 7       | 10   |

### Step 12

Page replacement reference string:
    7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 8

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 11   |
| 3     | 4       | 7    |
| 4     | 7       | 12   |

### Step 13

Page replacement reference string:
    8, 9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 8

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 13   |
| 3     | 4       | 7    |
| 4     | 7       | 12   |

### Step 14

Page replacement reference string:
    9, 7, 8, 9, 5, 4, 5, 4, 2

Faults: 9

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 13   |
| 3     | 9       | 14   |
| 4     | 7       | 12   |

### Step 15

Page replacement reference string:
    7, 8, 9, 5, 4, 5, 4, 2

Faults: 9

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 13   |
| 3     | 9       | 14   |
| 4     | 7       | 15   |

### Step 16

Page replacement reference string:
    8, 9, 5, 4, 5, 4, 2

Faults: 9

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 16   |
| 3     | 9       | 14   |
| 4     | 7       | 15   |

### Step 17

Page replacement reference string:
    9, 5, 4, 5, 4, 2

Faults: 9

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 1       | 8    |
| 1     | 6       | 9    |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 7       | 15   |

### Step 18

Page replacement reference string:
    5, 4, 5, 4, 2

Faults: 10

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 5       | 18   |
| 1     | 6       | 9    |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 7       | 15   |

### Step 19

Page replacement reference string:
    4, 5, 4, 2

Faults: 11

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 5       | 18   |
| 1     | 4       | 19   |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 7       | 15   |

### Step 20

Page replacement reference string:
    5, 4, 2

Faults: 11

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 5       | 20   |
| 1     | 4       | 19   |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 7       | 15   |

### Step 21

Page replacement reference string:
    4, 2

Faults: 11

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 5       | 20   |
| 1     | 4       | 21   |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 7       | 15   |

### Step 22

Page replacement reference string:
    2

Faults: 12

| Frame | Content | Last |
|:-----:| ------- | ---- |
| 0     | 5       | 20   |
| 1     | 4       | 21   |
| 2     | 8       | 16   |
| 3     | 9       | 17   |
| 4     | 2       | 22   |

