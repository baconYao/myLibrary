function HashTable(size) {
  this.buckets = Array(size);
  this.numBuckets = this.buckets.length;
}

function HashNode(key, value, next) {
  this.key = key;
  this.value = value;
  this.next = next || null;
}

// hash method
HashTable.prototype.hash = function(key) {
  var total = 0;
  var len = key.length;

  for(var i = 0; i < len; i++){
    // charCodeAt 取得ascii code
    total += key.charCodeAt(i);
  }
  var bucket = total % this.numBuckets;
  return bucket;
};

HashTable.prototype.insert = function(key, value) {
  var index = this.hash(key);
  // console.log('Index: ', index);
  if(!this.buckets[index]){
    this.buckets[index] = new HashNode(key, value);
  } else if(this.buckets[index].key === key){                   //check the first key of the bucket
    this.buckets[index].value = value;
  } else {
    var currentNode = this.buckets[index];
    while(currentNode.next){
      // update value
      if(currentNode.next.key === key){
        currentNode.next.value = value;
        return;
      }
      currentNode = currentNode.next;
    }
    currentNode.next = new HashNode(key, value);
  }
};

HashTable.prototype.get = function(key) {
  var index= this.hash(key);
  if(!this.buckets[index]){
    return null;
  } else {
    var currentNode = this.buckets[index];
    while(currentNode){
      if(currentNode.key === key){
        return currentNode.value;
      }
      currentNode = currentNode.next;
    }
    return null;

  }
};

HashTable.prototype.retrieveAll = function() {
  var allNodes = [];
  for(var i = 0; i < this.numBuckets; i++){
    var currentNode = this.buckets[i];
    while(currentNode){
      allNodes.push(currentNode);
      currentNode = currentNode.next;
    }
  }
  return allNodes;
};

// main---------------------------------------

var myHT = new HashTable(30);
// console.log(myHT.hash('Becca'));
myHT.insert('Dean', 'dean@gmail.com');
myHT.insert('bacon', 'bacon@gmail.com');
myHT.insert('Dane', 'daen@yahoo.com');
myHT.insert('Dane', 'OKOK!!@jdimlc.com');
myHT.insert('Joe', 'joey@facebook.com');
myHT.insert('Samantha', 'theas@twitter.com');

console.log(myHT.buckets);
// console.log(myHT.get('Dane'));
// console.log(myHT.retrieveAll());
