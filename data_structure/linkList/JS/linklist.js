function LinkedList(){
  this.head = null;
  this.tail = null;
}

function Node(value, next, prev){
  this.value = value;
  this.next = next;
  this.prev = prev
}

LinkedList.prototype.addToHead = function(value) {
  var newNode = new Node(value, this.head, null);     //this.head means LinkedList function
  if(this.head){
    this.head.prev = newNode;
  } else {
    this.tail = newNode;
  }
  this.head = newNode;
};

LinkedList.prototype.addToTail = function(value) {
  var newNode = new Node(value, null, this.tail);
  if(this.tail){
    this.tail.next = newNode;
  } else {
    this.head = newNode;
  }
  this.tail = newNode;
};

LinkedList.prototype.removeHead = function(){
  // Link list is empty
  if(!this.head){
    return null;
  }
  var val = this.head.value;
  this.head = this.head.next;
  if(this.head){
    this.head.prev = null;
  } else {
    this.tail = null;
  }
  return val;
};

LinkedList.prototype.removeTail = function(){
  // Link list is empty
  if(!this.tail){
    return null;
  }
  var val = this.tail.value;
  this.tail = this.tail.prev;
  if(this.tail){
    this.tail.next = null;
  } else {
    this.head = null;
  }
  return val;
};

LinkedList.prototype.search = function(searchValue){
  var currentNode = this.head;
  while(currentNode)
  {
    if(currentNode.value === searchValue){
      return currentNode.value;
    }
    currentNode = currentNode.next;
  }
  return null;
};

LinkedList.prototype.indexOf = function(Value){
  var currentNode = this.head;
  var index = [];
  var indexCount = 0;
  while(currentNode){
    if(currentNode.value === Value){
      index.push(indexCount);
    }
    currentNode = currentNode.next
    indexCount++;
  }
  return index;
}

var myLL = new LinkedList();
myLL.addToTail(10);
myLL.addToTail(30);
myLL.addToTail('hello');
myLL.addToTail(10);
myLL.addToTail(20);
myLL.addToTail(120);
myLL.addToTail('world');
myLL.addToTail(130);

console.log(myLL.indexOf(10));


