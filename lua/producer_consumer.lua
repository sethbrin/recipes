#!/usr/bin/lua
-- use coroutine to implement producer-consumer model

local newProducer

function producer()
  local i = 0
  while true do
    i = i + 1
    send(i)
  end
end

function consumer()
  while true do
    local i = receive()
    print(i)
  end
end

function receive()
  local status, value = coroutine.resume(newProducer)
  return value
end

function send(x)
  coroutine.yield(x)
end

-- start
newProducer = coroutine.create(producer)
consumer()
