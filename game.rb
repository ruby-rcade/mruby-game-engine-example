@x = 100
@y = 100

def input_received(input)
  # puts "Called input_received method with input: #{input.inspect}"
  case input
  when :left  then @x -= 1
  when :right then @x += 1
  when :up    then @y -= 1
  when :down  then @y += 1
  end
  puts "Current x/y: #{@x}, #{@y}"
end

def render
  Engine.draw_square(@x, @y, 100) # call C code
rescue => e
  puts "Error in render: " + e.message
end
