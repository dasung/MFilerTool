# Code Review for MFilerTool

## General Observations
1. **Project Structure**: The project is well-organized with clear separation of concerns between source files, headers, and common utilities.
2. **Documentation**: The `README.md` provides a good overview of the project, setup instructions, and tested scenarios. However, it could benefit from more detailed explanations of the core functionality and design decisions.

## Specific Feedback

### 1. `main.cpp`
- **Strengths**:
  - The main function is concise and clearly outlines the program's flow.
  - Proper use of threads for input and processing tasks.
- **Improvements**:
  - Error handling for `inputObj.init(inputFileName)` could provide more detailed feedback to the user.
  - Consider adding comments to explain the purpose of each thread and their interactions.

### 2. `Logger.h`
- **Strengths**:
  - Implements a singleton pattern effectively with thread safety.
  - Provides macros for easy logging control.
- **Improvements**:
  - The destructor comment could be clarified for better readability.
  - Typo in the comment: "privent" should be "prevent".

### 3. `TransferQueue.h`
- **Strengths**:
  - Well-defined structure for `MarketData` and clear enumeration for `MarketEventID`.
  - Proper use of mutex and condition variables for thread-safe queue operations.
- **Improvements**:
  - Add comments to describe the purpose of each method in the `TransferQueue` class.
  - Consider renaming `sendStopperEvent` to something more descriptive, like `enqueueStopperEvent`.

### 4. `Makefile`
- **Strengths**:
  - Comprehensive rules for building, linking, and cleaning the project.
  - Precompiled headers are used to optimize compilation.
- **Improvements**:
  - Add a `help` target to describe available commands for new developers.
  - Consider adding a `test` target to automate running test cases.

### 5. `InputHandler.cpp` and `InputHandler.h`
- **Strengths**:
  - The `InputHandler` class is well-structured and handles file parsing effectively.
  - Proper use of `std::stringstream` for parsing CSV lines.
- **Issues**:
  - Typo in the `DataRow` struct: `quntity` should be `quantity`.
  - Error handling for file operations could be more robust. For example, checking for specific error codes or exceptions when opening files.
  - The `parseInputFile` method skips rows with errors but does not log or track them for debugging purposes.

### 6. `OutputProcessor.cpp` and `OutputProcessor.h`
- **Strengths**:
  - The `OutputProcessor` class efficiently processes and organizes market data using a map and set with a custom sorting operator.
  - Proper use of RAII for file handling in `generateOutput`.
- **Issues**:
  - The `generateOutput` method does not handle cases where the output directory might not exist or is unwritable.
  - The `debugMarketDataMap` method is unused in the current implementation. Consider removing it or integrating it for debugging purposes.
  - Potential performance bottleneck in `insertDataToMap` when handling large datasets due to repeated map lookups.

### 7. `TransferQueue.cpp` and `TransferQueue.h`
- **Strengths**:
  - Implements a thread-safe queue using `std::mutex` and `std::condition_variable`.
  - Clear separation of methods for pushing and popping data.
- **Issues**:
  - The `sendStopperEvent` method uses `-1` for `seqNumber` and `quantity`, which might lead to confusion. Consider using a more explicit constant or enum value.
  - No mechanism to handle spurious wakeups in `popData`. While unlikely, it is a good practice to recheck the condition after waking up.

## Recommendations
1. **Code Quality**:
   - Fix typos and improve variable naming for clarity (e.g., `quntity` → `quantity`).
   - Add comments to explain the purpose of key methods and classes.

2. **Error Handling**:
   - Improve error handling for file operations and thread synchronization.
   - Log skipped rows in `InputHandler::parseInputFile` for debugging.

3. **Performance**:
   - Optimize `OutputProcessor::insertDataToMap` for large datasets.
   - Consider using a more efficient data structure for `m_MarketDataMap` if performance becomes an issue.

4. **Testing**:
   - Add unit tests for edge cases, such as malformed CSV files, large datasets, and invalid input.