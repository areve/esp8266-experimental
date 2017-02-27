import { Component, OnInit, Inject } from '@angular/core'
import { BotService } from './bot.service'

@Component({
  providers: [BotService],
  template: `
    <main class="serial-parallel-main">
      <h1>Bot</h1>
      <p>Control a bot</p>
      <form>
        <button (click)="forwards()">Forwards</button>
        <button (click)="backwards()">Backwards</button>
        <button (click)="left()">Left</button>
        <button (click)="right()">Right</button>
        <button (click)="stop()">Stop</button>
      </form>
    </main>
  `
})

export class SerialParallelComponent {
  public latchPin: string = 'D5'
  public clockPin: string = 'D0'
  public dataPin: string = 'D6'
  public interval: number = 100000
  public pins: string[] = ['D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'D8']
  private botService: BotService

  constructor ( @Inject(BotService) botService: BotService) {
    this.botService = botService;
  }

  forwards () {
    this.botService.forwards()
      .subscribe(console.log, console.error)
  }

  stop () {
    this.botService.stop()
      .subscribe(console.log, console.error)
  }

  backwards () {
    this.botService.backwards()
      .subscribe(console.log, console.error)
  }

  right () {
    this.botService.right()
      .subscribe(console.log, console.error)
  }

  left () {
    this.botService.left()
      .subscribe(console.log, console.error)
  }
}
