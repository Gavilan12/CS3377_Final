i=1
PointsInSquare=$(($1))
PointsInQuarterCircle=0
for i in $(seq $PointsInSquare); do
read x y < <(awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand(), rand()}')
X=$(bc <<< "scale=7; $x*$x")
Y=$(bc <<< "scale=7; $y*$y")
XY=$(bc <<< "scale=7; $X+$Y")
if(( $(echo "$XY<=1.000" |bc -l) )); then
((PointsInQuarterCircle++))
fi
((i++))
done

MyPi=$(bc <<< " scale=5; (($PointsInQuarterCircle / $PointsInSquare) * 4 )/1  ")

echo "PointsInQuarterCircle $PointsInQuarterCircle : PointsInSquare $PointsInSquare"
echo "MyPi = $MyPi"


