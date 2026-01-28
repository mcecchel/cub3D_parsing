#!/bin/bash
# ============================================
# CUB3D PARSING TEST SUITE
# ============================================

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS=0
FAIL=0

# Function to run a test
run_test() {
    local test_name="$1"
    local map_file="$2"
    local should_pass="$3"
    
    echo -e "${YELLOW}Testing: $test_name${NC}"
    ./cub3D "$map_file" > /dev/null 2>&1
    result=$?
    
    if [ "$should_pass" = "pass" ]; then
        if [ $result -eq 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}: $test_name"
            ((PASS++))
        else
            echo -e "${RED}✗ FAIL${NC}: $test_name (Expected pass, got fail)"
            ((FAIL++))
        fi
    else
        if [ $result -ne 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}: $test_name (Correctly rejected)"
            ((PASS++))
        else
            echo -e "${RED}✗ FAIL${NC}: $test_name (Expected fail, got pass)"
            ((FAIL++))
        fi
    fi
    echo ""
}

# Create test directory
mkdir -p test_maps

# ============================================
# TEST 1: Valid Simple Map
# ============================================
cat > test_maps/valid_simple.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111111
EOF

run_test "Valid Simple Map" "test_maps/valid_simple.cub" "pass"

# ============================================
# TEST 2: Map with Spaces
# ============================================
cat > test_maps/valid_spaces.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 0,200,100
C 100,150,200

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111 1110101 101111010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
EOF

run_test "Valid Map with Spaces" "test_maps/valid_spaces.cub" "pass"

# ============================================
# TEST 3: Missing Texture
# ============================================
cat > test_maps/missing_texture.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Missing East Texture" "test_maps/missing_texture.cub" "fail"

# ============================================
# TEST 4: Duplicate Texture
# ============================================
cat > test_maps/duplicate_texture.cub << 'EOF'
NO ./textures/north.xpm
NO ./textures/north2.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Duplicate North Texture" "test_maps/duplicate_texture.cub" "fail"

# ============================================
# TEST 5: Invalid RGB Values
# ============================================
cat > test_maps/invalid_rgb.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 300,100,0
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Invalid RGB Value (>255)" "test_maps/invalid_rgb.cub" "fail"

# ============================================
# TEST 6: Negative RGB
# ============================================
cat > test_maps/negative_rgb.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,-10,0
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Negative RGB Value" "test_maps/negative_rgb.cub" "fail"

# ============================================
# TEST 7: Invalid RGB Format
# ============================================
cat > test_maps/invalid_rgb_format.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Invalid RGB Format (only 2 values)" "test_maps/invalid_rgb_format.cub" "fail"

# ============================================
# TEST 8: No Player
# ============================================
cat > test_maps/no_player.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
101001
100001
111111
EOF

run_test "No Player in Map" "test_maps/no_player.cub" "fail"

# ============================================
# TEST 9: Multiple Players
# ============================================
cat > test_maps/multiple_players.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
1000S1
111111
EOF

run_test "Multiple Players" "test_maps/multiple_players.cub" "fail"

# ============================================
# TEST 10: Invalid Character in Map
# ============================================
cat > test_maps/invalid_char.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100X01
101001
1000N1
111111
EOF

run_test "Invalid Character in Map" "test_maps/invalid_char.cub" "fail"

# ============================================
# TEST 11: Open Map (Not Closed)
# ============================================
cat > test_maps/open_map.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111110
EOF

run_test "Open Map (Bottom Right)" "test_maps/open_map.cub" "fail"

# ============================================
# TEST 12: Map with Holes
# ============================================
cat > test_maps/map_holes.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

11111111
10000001
10 N0001
10000001
11111111
EOF

run_test "Map with Space Creating Hole" "test_maps/map_holes.cub" "fail"

# ============================================
# TEST 13: Wrong File Extension
# ============================================
echo "Test content" > test_maps/wrong_ext.txt
run_test "Wrong File Extension (.txt)" "test_maps/wrong_ext.txt" "fail"

# ============================================
# TEST 14: Non-existent File
# ============================================
run_test "Non-existent File" "test_maps/nonexistent.cub" "fail"

# ============================================
# TEST 15: Empty File
# ============================================
touch test_maps/empty.cub
run_test "Empty File" "test_maps/empty.cub" "fail"

# ============================================
# TEST 16: All Player Directions
# ============================================
for dir in N S E W; do
    cat > test_maps/player_${dir}.cub << EOF
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
101001
1000${dir}1
111111
EOF
    run_test "Player Direction: $dir" "test_maps/player_${dir}.cub" "pass"
done

# ============================================
# TEST 17: RGB with Extra Commas
# ============================================
cat > test_maps/extra_commas.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0,
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "RGB with Extra Comma" "test_maps/extra_commas.cub" "fail"

# ============================================
# TEST 18: Whitespace Before/After Values
# ============================================
cat > test_maps/whitespace_values.cub << 'EOF'
NO    ./textures/north.xpm  
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F   220  ,  100  ,  0  
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Whitespace Around Values" "test_maps/whitespace_values.cub" "pass"

# ============================================
# TEST 19: Map with Empty Lines Inside
# ============================================
cat > test_maps/empty_lines_map.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001

1000N1
111111
EOF

run_test "Empty Lines Inside Map" "test_maps/empty_lines_map.cub" "fail"

# ============================================
# TEST 20: Large Map
# ============================================
cat > test_maps/large_map.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

11111111111111111111111111111111111111111111111111
10000000000000000000000000000000000000000000000001
10111111111111111111111111111111111111111111111101
10100000000000000000000000000000000000000000000101
10101111111111111111111111111111111111111111110101
10101000000000000000000000000000000000000000010101
10101011111111111111111111111111111111111111010101
10101010000000000000000000000000000000000000010101
10101010111111111111111111111111111111111110010101
10101010100000000000000000000000000000000010010101
10101010101111111111111111111111111111111010010101
10101010101N00000000000000000000000000000010010101
10101010101111111111111111111111111111111010010101
10101010100000000000000000000000000000000010010101
10101010111111111111111111111111111111111110010101
10101010000000000000000000000000000000000000010101
10101011111111111111111111111111111111111111010101
10101000000000000000000000000000000000000000010101
10101111111111111111111111111111111111111111110101
10100000000000000000000000000000000000000000000101
10111111111111111111111111111111111111111111111101
10000000000000000000000000000000000000000000000001
11111111111111111111111111111111111111111111111111
EOF

run_test "Large Map" "test_maps/large_map.cub" "pass"

# ============================================
# SUMMARY
# ============================================
echo "========================================"
echo -e "${GREEN}Tests Passed: $PASS${NC}"
echo -e "${RED}Tests Failed: $FAIL${NC}"
echo "========================================"

# Cleanup
# rm -rf test_maps

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi