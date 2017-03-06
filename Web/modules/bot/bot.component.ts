import { Component, OnInit, Inject, ViewChild, ElementRef } from '@angular/core'
import { BotService } from './bot.service'
import { Observable } from 'rxjs/Rx'

@Component({
  providers: [BotService],
  template: `
    <main class="bot-main">
      <h1>Bot</h1>
      <p>Control a bot</p>
      <form>
        <div class="buttons">
          <button (click)="forwards()">Forwards</button>
          <button (click)="backwards()">Backwards</button>
          <button (click)="left()">Left</button>
          <button (click)="right()">Right</button>
          <button (click)="stop()">Stop</button>
          <button (click)="startUltraSound()">Start UltraSound</button>
          <button (click)="readUltraSound()">Read UltraSound</button>
        </div>
        <ul>
          <li><span>ultraSoundDistance:</span> <strong>{{ultraSoundDistance}}mm</strong></li>
          <li><span>x:</span> <strong>{{bot.x}}</strong></li>
          <li><span>y:</span> <strong>{{bot.y}}</strong></li>
          <li><span>angle:</span> <strong>{{bot.angle | number : '1.3-3'}}</strong></li>
        </ul>
        <canvas #canvas width="500" height="300"></canvas>
      </form>
    </main>
  `
})

export class BotComponent {
  public latchPin: string = 'D5'
  public clockPin: string = 'D0'
  public dataPin: string = 'D6'
  public interval: number = 100000
  public pins: string[] = ['D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'D8']
  public canvasWidth: number = 500
  public canvasHeight: number = 300
  public scale: number = 0.1
  public dotSize: number = 2
  public ultraSoundDistance: number = 0
  public bot: { x: number, y: number, angle: number } = { x: 0, y: 0, angle: 0 }
  @ViewChild('canvas') canvas: ElementRef
  private botService: BotService
  private ctx: CanvasRenderingContext2D

  constructor( @Inject(BotService) botService: BotService) {
    this.botService = botService
  }

  ngAfterViewInit() {
    this.ctx = this.canvas.nativeElement.getContext('2d')
    this.canvas.nativeElement.height =
      this.canvasHeight =
      this.canvas.nativeElement.offsetHeight
    this.canvas.nativeElement.width =
      this.canvasWidth =
      this.canvas.nativeElement.offsetWidth

    this.ctx.strokeStyle = 'none'
    this.update()

    this.botService._listeners.push(
      ({medianDistance, lastDistances}) => {
        console.log('medianDistance: ', medianDistance)
        this.ultraSoundDistance = medianDistance
        this.drawUltraSound()
      })

    // Observable.interval(500).subscribe(() => {
    //   this.bot.angle += 0.136
    //   this.botService
    //     .readUltraSound()
    //     .subscribe(({medianDistance, lastDistances}) => {
    //       this.ultraSoundDistance = medianDistance
    //       this.drawUltraSound()
    //     }, console.error)
    //   this.botService
    //     .requestUltraSound()
    // })
  }

  update() {
    this.drawBackground()
    this.drawBot()
  }

  drawUltraSound() {
    let x = this.bot.x + Math.sin(this.bot.angle) * this.ultraSoundDistance
    let y = this.bot.y + Math.cos(this.bot.angle) * this.ultraSoundDistance

    this.drawPoint(x, y)
  }

  drawPoint(x: number, y: number) {
    this.ctx.fillStyle = '#000'
    this.ctx.fillRect(
      this.bot.x + x * this.scale - this.dotSize / 2 + this.canvasWidth / 2,
      -this.bot.y + y * this.scale - this.dotSize / 2 + this.canvasHeight / 2,
      this.dotSize, this.dotSize)
  }

  drawBackground() {
    this.ctx.fillStyle = '#fff'
    this.ctx.fillRect(0, 0, this.canvasWidth, this.canvasHeight)
  }

  drawBot() {
    let x = this.canvasWidth / 2
    let y = this.canvasHeight / 2
    this.ctx.fillStyle = '#009'
    this.ctx.fillRect(this.bot.x * this.scale + x - 4, this.bot.y * this.scale + y - 8, 8, 16)
    this.ctx.beginPath()
    this.ctx.moveTo(this.bot.x * this.scale + x - 8, this.bot.y * this.scale + y - 8)
    this.ctx.lineTo(this.bot.x * this.scale + x, this.bot.y * this.scale + y - 16)
    this.ctx.lineTo(this.bot.x * this.scale + x + 8, this.bot.y * this.scale + y - 8)
    this.ctx.fill()
  }

  forwards() {
    this.botService.forwards()
      .subscribe(console.log, console.error)
    this.bot.y -= 10
  }

  stop() {
    this.botService.stop()
      .subscribe(console.log, console.error)
  }

  backwards() {
    this.botService.backwards()
      .subscribe(console.log, console.error)
    this.bot.y += 10
  }

  right() {
    this.botService.right()
      .subscribe(console.log, console.error)
  }

  left() {
    this.botService.left()
      .subscribe(console.log, console.error)
  }

  startUltraSound() {
    this.botService.startUltraSound()
      .subscribe(console.log, console.error)
  }

  readUltraSound() {
    this.botService
      .requestUltraSound()
    //    this.botService.readUltraSound()
    //    .subscribe(console.log, console.error)
  }
}
