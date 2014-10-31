@x = 100
@y = 100

def on_key_press(input)
  puts "Called on_key_press method with input: #{input.inspect}"
  case input
  when :left,  'Left'  then @x -= 10
  when :right, 'Right' then @x += 10
  when :up,    'Up'    then @y -= 10
  when :down,  'Down'  then @y += 10
  end
  puts "Current x/y: #{@x}, #{@y}"
end

def while_key_down(input)
  # puts "Called while_key_down method with input: #{input.inspect}"
  case input
  when :left,  'Left'  then @x -= 10
  when :right, 'Right' then @x += 10
  when :up,    'Up'    then @y -= 10
  when :down,  'Down'  then @y += 10
  end
  # puts "Current x/y: #{@x}, #{@y}"
end

def render
  Engine.draw_square(@x, @y, 100) # call C code
rescue => e
  puts "Error in render: " + e.message
end
