# Memory Safety and Programming Language Design
This is the webpage of course COMP737011 Memory Safety and Programming Language Design for postgraduate students at Fudan University. The course will first go through the Foundations of Memory Safety Problem; then we will teach the Rust Programming Language by focusing on its special design for memory-safety protection; finally we will share some advanced topics useful for mitigating memory-safety issues.

- Term: 2025 Spring  
- Classroom: JB102  
- Time: Tuesday 18:30-21:05  
- Instructor: Dr. Hui Xu

## Part I: Foundations of Memory Safety 

| Date | Topic | Materials | Code |
|---|---|---|---|
| Week1 | Introduction, Stack Smashing | [slides1](slides/l0-intro.pdf), [slides2](slides/l1-stacksmash.pdf), [notes](notes/l1-stacksmash.md) | [vuln.c](code/l1-vuln.c), [shell.c](code/l1-shell.c), [exstack.py](code/l1-exstack.py), [shell.c](code/l1-aslr.c), [rop.py](code/l1-rop.py) |
| Week2 | Allocator Design | [slides](slides/l2-allocator.pdf) | [allocator.c](code/l2-allocator.c) |
| Week3 | Heap Attack | [slides](slides/l3-heapattack.pdf) | [heaptoy.c](code/l3-heaptoy.c) | 
| Week4 | Memory Exhaustion | [slides](slides/l4-memexhaustion.pdf) | [stackoverflow.c](code/l4-stackoverflow.c), [stackhandle](code/l4-stackhandle.c), [heap](code/l4-heap.c), [smallheap](code/l4-smallheap.c) |
| Week5 | Concurrency | [slides](slides/l5-concurrency.pdf) | [atomicint.c](code/l5-atomicint.c), [membarrier1](code/l5-membarrier1.c), [membarrier2](/code/l5-membarrier2.c) |

## Part II: Rust Programming Language 

| Date | Topic | Materials | Code |
|---|---|---|---|
| Week6 | Rust Ownership | [slides](slides/l6-rust-owner.pdf) | [ownership.rs](code/l6-ownership.rs),[mutability.rs](code/l6-mutability.rs),[lifetime.rs](code/l6-lifetime.rs),[list-unsafe.rs](code/l6-list-unsafe.rs),[list-safe.rs](code/l6-list-safe.rs)| 
| Week7 | Rust Type System | [Slides](slides/l7-rust-type.pdf) | [sinlist.rs](code/l7-sinlist.rs) | 
| Week8 | Rust Concurrency | [Slides](slides/l8-rust-concurrency.pdf) | [check_send_sync.rs](code/l8-check_send_sync.rs), [sinlist.rs](code/l8-sinlist.rs), [sinlist.rs](code/l8-unsend.rs) | 
| Week9 | More Features of Rust | [Slides](slides/l9-rust-more.pdf) |  |
| Week10 | Rust Toolchain | [Slides](slides/l10-rust-toolchain.pdf) | |

## Part III: Advanced Topics

| Date | Topic | Materials  |
|---|---|---|
| Week11 | Alias Analysis | [Slides](slides/l11-aliasanalysis.pdf) |
| Week12 | Alias Analysis |  | 
| Week13 |  |  | 
| Week14 |  |  | 
| Week15 |  |  |
| Week16 |  |  |
