class Vector2:
    def __init__(self, x=0, y=0): # [AI] Merged constructors and String constructor
        if isinstance(x, str):
            pos = x.find('_')
            self.x = int(x[:pos])
            self.y = int(x[pos + 1:])
        else:
            self.x = x
            self.y = y

    def __str__(self):
        return f"{self.x}_{self.y}"

    def __eq__(self, other):
        if self is other:
            return True
        if other is None or not isinstance(other, Vector2):
            return False
        return self.x == other.x and self.y == other.y

    def add(self, other):
        return Vector2(self.x + other.x, self.y + other.y)

    def addSelf(self, other):
        self.x += other.x
        self.y += other.y

    def multiply(self, scale):
        return Vector2(int(self.x * scale), int(self.y * scale))

    def multiplySelf(self, scale):
        self.x *= scale
        self.y *= scale

Vector2.ZERO = Vector2(0, 0) # [AI] Added static ZERO after class definition
