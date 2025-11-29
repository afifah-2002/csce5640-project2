import random

# Configuration
frame_counts = [3, 5, 10, 15, 20, 25, 30]
tests_per_category = 5
reference_string_length = 100
page_range = (1, 50)  # Pages from 1 to 50

for frames in frame_counts:
    for test_num in range(1, tests_per_category + 1):
        filename = f"test_{frames}frames_{test_num}.txt"
        
        # Generate random reference string
        ref_string = [random.randint(page_range[0], page_range[1]) 
                     for _ in range(reference_string_length)]
        
        # Write to file
        with open(filename, 'w') as f:
            f.write(f"frames: {frames}\n")
            f.write(f"reference_string: {' '.join(map(str, ref_string))}\n")
        
        print(f"Created {filename}")

print(f"\nTotal test files created: {len(frame_counts) * tests_per_category}")