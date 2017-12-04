array = Array.new(4000000, false)

maxSize=2000000
half = (maxSize/2)
tenper=(maxSize/10)

x=1
y=1


while x < half do
    x+=1
    y=2
    while y < tenper do
        z=x*y
        y+=1
        array[z]=true
        if (z>=maxSize)
            break
        end
    end
end

i=1
total=0
while i < maxSize
    if(array[i] == false)
        total+=i
    end
    i+=1
end
total-=1
puts (total.to_s)