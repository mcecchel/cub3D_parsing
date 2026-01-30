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
# TEST 4: Texture file not existing
# ============================================
cat > test_maps/texture_not_found.cub << 'EOF'
NO ./textures/nonexistent.xpm
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

run_test "Texture File Not Found" "test_maps/texture_not_found.cub" "fail"

# ============================================
# TEST 5: No space after identifier
# ============================================
cat > test_maps/no_space_identifier.cub << 'EOF'
NO./textures/north.xpm
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

run_test "No Space After Identifier" "test_maps/no_space_identifier.cub" "fail"

# ============================================
# TEST 6: Duplicate Texture
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

run_test "Duplicate Texture" "test_maps/duplicate_texture.cub" "fail"

# ============================================
# TEST 7: Duplicate floor/ceiling
# ============================================
cat > test_maps/duplicate_floor.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
F 100,200,0
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Duplicate Color" "test_maps/duplicate_floor.cub" "fail"

# ============================================
# TEST 8: Invalid RGB Values
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
# TEST 9: RGB with empty values
# ============================================
cat > test_maps/empty_rgb_values.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F ,,
C 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Empty RGB Values" "test_maps/empty_rgb_values.cub" "fail"

# ============================================
# TEST 10: Negative RGB
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
# TEST 11: Invalid RGB Format
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
# TEST 12: RGB with leading zeros
# ============================================
cat > test_maps/rgb_leading_zeros.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 001,002,003
C 000,255,000

111111
100001
1000N1
111111
EOF

run_test "RGB with Leading Zeros" "test_maps/rgb_leading_zeros.cub" "pass"

# ============================================
# TEST 13: Lowercase identifiers (F/C)
# ============================================
cat > test_maps/lowercase_identifiers.cub << 'EOF'
no ./textures/north.xpm
so ./textures/south.xpm
we ./textures/west.xpm
ea ./textures/east.xpm

f 220,100,0
c 225,30,0

111111
100001
1000N1
111111
EOF

run_test "Lowercase Identifiers" "test_maps/lowercase_identifiers.cub" "fail"

# ============================================
# TEST 14: RGB boundary values (0 and 255)
# ============================================
cat > test_maps/rgb_boundaries.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 0,0,0
C 255,255,255

111111
100001
1000N1
111111
EOF

run_test "RGB Boundary Values (0 and 255)" "test_maps/rgb_boundaries.cub" "pass"

# ============================================
# TEST 15: Map before config elements
# ============================================
cat > test_maps/map_before_config.cub << 'EOF'
111111
100001
1000N1
111111

NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0
EOF

run_test "Map Before Config Elements" "test_maps/map_before_config.cub" "fail"

# ============================================
# TEST 16: Map with only walls
# ============================================
cat > test_maps/only_walls.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
111111
111111
111N11
111111
EOF

run_test "Map with Player Surrounded by Walls" "test_maps/only_walls.cub" "pass"

# ============================================
# TEST 17: No Player
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
# TEST 18: Multiple Players
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
# TEST 19: Player on edge (wall)
# ============================================
cat > test_maps/player_on_edge.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111
N000001
1000001
1000001
1111111
EOF

run_test "Player on Map Edge" "test_maps/player_on_edge.cub" "fail"

# ============================================
# TEST 20: Invalid Character in Map
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
# TEST 21: Open Map (Not Closed)
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
# TEST 22: Map with Holes
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
# TEST 23: Map with spaces on edges
# ============================================
cat > test_maps/spaces_on_edges.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

  1111111
  1000001
  100N001
  1000001
  1111111
EOF

run_test "Map with Leading Spaces (Valid)" "test_maps/spaces_on_edges.cub" "pass"

# ============================================
# TEST 24: Tabs instead of spaces
# ============================================
cat > test_maps/tabs_in_config.cub << 'EOF'
NO	./textures/north.xpm
SO	./textures/south.xpm
WE	./textures/west.xpm
EA	./textures/east.xpm

F	220,100,0
C	225,30,0

111111
100001
1000N1
111111
EOF

# Da subject non si parla di whitespaces ma di spaces
# "each type of information from an element can be separated
# by one or more spaces" quindi accanna.
run_test "Tabs in Config Lines" "test_maps/tabs_in_config.cub" "fail"

# ============================================
# TEST 25: Irregular rectangular map
# ============================================
cat > test_maps/irregular_shape.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

11111
10001111
100000N1
10001111
11111
EOF

run_test "Irregular Shape Map" "test_maps/irregular_shape.cub" "pass"

# ============================================
# TEST 26: Tiny invalid map
# ============================================
cat > test_maps/tiny_map.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

N
EOF

run_test "Tiny Map (1x1)" "test_maps/tiny_map.cub" "fail"

# ============================================
# TEST 27: Extra content after map
# ============================================
cat > test_maps/content_after_map.cub << 'EOF'
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

This should not be here
EOF

run_test "Content After Map" "test_maps/content_after_map.cub" "fail"

# ============================================
# TEST 28: Minimal valid map
# ============================================
cat > test_maps/minimal_valid.cub << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111
1N1
111
EOF

run_test "Minimal Valid Map (3x3)" "test_maps/minimal_valid.cub" "pass"

# ============================================
# TEST 29: Wrong File Extension
# ============================================
echo "Test content" > test_maps/wrong_ext.txt
run_test "Wrong File Extension (.txt)" "test_maps/wrong_ext.txt" "fail"

# ============================================
# TEST 30: Non-existent File
# ============================================
run_test "Non-existent File" "test_maps/nonexistent.cub" "fail"

# ============================================
# TEST 31: Empty File
# ============================================
touch test_maps/empty.cub
run_test "Empty File" "test_maps/empty.cub" "fail"

# ============================================
# TEST 32: All Player Directions
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
# TEST 33: RGB with Extra Commas
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
# TEST 34: Spaces Before/After Values
# ============================================
cat > test_maps/space_values.cub << 'EOF'
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

run_test "Space Around Values" "test_maps/space_values.cub" "pass"

# ============================================
# TEST 35: Map with Empty Lines Inside
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
# TEST 36: Large Map
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
    echo -e "${GREEN}All tests passed, DAI CAZZOOOOOO!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi