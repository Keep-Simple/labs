// @ts-nocheck
import { RcFile } from "antd/lib/upload"
import {
  getTicketsValidationErrors,
  Ticket,
  ticketsSerializer,
  TicketsValidatorReturnType,
} from "./schemas"
import { message, notification } from "antd"

class TicketsPersister {
  fileName: string

  constructor(fileName?: string) {
    this.fileName = fileName || "tickets"
  }

  downloadFileWithTickets(tickets: Ticket[]) {
    if (!tickets.length) return

    const errors = getTicketsValidationErrors(tickets)

    if (errors.length) {
      this.displayErrors(errors)
      return
    }

    const raw = ticketsSerializer(tickets)
    const encodedObj = URL.createObjectURL(
      new Blob([raw], {
        type: "application/json",
      })
    )
    // create "a" HTLM element with href to file
    const link = document.createElement("a")
    link.href = encodedObj
    link.download = `${this.fileName}.json`
    document.body.appendChild(link)
    link.click()

    // clean up "a" element & remove ObjectURL
    document.body.removeChild(link)
    URL.revokeObjectURL(encodedObj)
  }

  loadFromFile(file: RcFile, onLoad: (tickets: Ticket[]) => void) {
    const reader = new FileReader()
    reader.readAsText(file)
    reader.onload = () => {
      const raw = reader.result?.toString() || "[]"
      let tickets: Ticket[] = []
      let errors: TicketsValidatorReturnType = []

      try {
        tickets = JSON.parse(raw)
      } catch (e) {
        if (e instanceof Error) {
          errors.push({
            message: `File is corrupted (wrong json)`,
            meta: e.message,
          })
        }
      }
      errors.push(...getTicketsValidationErrors(tickets))

      if (errors.length) {
        this.displayErrors(errors)
        return
      }

      if (tickets.length) {
        onLoad(tickets)
        message.success(`Loaded tickets from ${file.name}`)
      } else {
        message.info(`File ${file.name} was emtpy`)
      }
    }
  }

  private displayErrors(errors: TicketsValidatorReturnType) {
    if (!errors?.length) return

    errors.forEach((e) =>
      notification.error({
        message: `${e.message}`,
        description: `Please fix the detected error: ${e.meta}`,
        placement: "bottomLeft",
        duration: 30,
      })
    )
  }
}

export const ticketsPersistor = new TicketsPersister()

export const capitalize = (s: any) => {
  if (typeof s !== "string") return ""
  return s.charAt(0).toUpperCase() + s.slice(1)
}

export class TicketsUtils {
  static mostUsedTicket(tickets: Ticket[]) {
    const stats = {}
    let mostUsed = null
    for (let ticket of tickets) {
      stats[ticket.ticketType] ??= 0
      stats[ticket.ticketType] += 1

      if (mostUsed == null) {
        mostUsed = ticket.ticketType
      } else {
        mostUsed =
          stats[ticket.ticketType] > stats[mostUsed]
            ? ticket.ticketType
            : mostUsed
      }
    }

    if (mostUsed == null) {
      return null
    }

    return {
      ticketType: mostUsed,
      count: stats[mostUsed],
    } as const
  }
}
